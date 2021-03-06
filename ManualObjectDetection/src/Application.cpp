#include "../include/pch.h"
#include "../include/Application.h"


Application::Application() = default;


Application::~Application()
{
	for (auto *flag : categoryChecker) {
		delete flag;
	}
	delete writer;
}

Application::Application(WindowSize size)
{
}

void Application::run(std::string &videoFilePath, int secondToStart, int step)
{
    if (fs::is_directory(videoFilePath)) {
        videoLoader = std::make_unique<LoadImagesFromDirectory>(videoFilePath);
    } else {
        videoLoader = std::make_unique<LoadImagesFromVideo>(videoFilePath, secondToStart, step);

    }
	loader.loadClasses();
	writer = new Writer("./detected.csv");
	inicializeCategoryChecker();
	while (!endApplication) {
		currentFrameBoundingBoxes.clear();
		if (backward_frame) {
            processFrame(videoLoader->getPreviousFrame());
		} else {
            processFrame(videoLoader->getNextFrame());
        }
	}
}

std::string Application::pickClass()
{
	cv::namedWindow(classPickerFrameName);
	cv::moveWindow(classPickerFrameName, 1300, 10);
	cvui::init(classPickerFrameName);
	//cvui::watch(classPickerFrameName);
	cv::Mat frame = cv::Mat((2 + loader.getClasses().size()) * 40, 500, CV_8UC3);
	unsigned int size = loader.getClasses().size();
    auto frameNumberTrackbar = (double) videoLoader->getFrameNumber();
	addAnotherObject = false;
	int i = 0;
	bool ESC_PRESSED = false;
	while (!ESC_PRESSED) {
        int key = cv::waitKey(20);
        if (key == 27) {
            ESC_PRESSED = true;
        }
        if (key == 115) {
            videoLoader->setPosition((unsigned int) frameNumberTrackbar - (unsigned int)videoLoader->getStep());
            break;
        }
	    frame = cv::Scalar(49, 52, 49);
		i = 0;
		for (const auto &entry : loader.getClasses()) {
			cvui::checkbox(frame, 50, i * 20 + 50, entry, categoryChecker[i]);
			i++;
		}
		if (cvui::button(frame, 220, i * 20 + 100, "ALL OBJECTS FOUND")) {
			break;
		}
		if (cvui::button(frame, 50, i * 20 + 100, "ADD ANOTHER")) {
			addAnotherObject = true;
			break;
		}
		if (cvui::button(frame, 50, (i +2) * 20 + 100, "END APPLICATION")) {
			endApplication = true;
			break;
		}
		cvui::text(frame, 50, i * 20 + 180, "Please press S to set frame according to the trackbar");
		cvui::trackbar(frame, 50, i*20 + 200, 200, &frameNumberTrackbar, 0., (double)videoLoader->getNumberOfFrames());
		cvui::update();
		// Show everything on the screen
		cv::imshow(classPickerFrameName, frame);
	}
	cv::destroyWindow(classPickerFrameName);
	return getPickedClassName();
}

std::string Application::getPickedClassName()
{
	std::string pickedClass = "None";
	for (int i = 0; i < categoryChecker.size(); i++) {
		if (*categoryChecker[i] == true) {
			pickedClass = loader.getClasses()[i];
		}
		*categoryChecker[i] = false;
	}
	return pickedClass;
}

cv::Rect Application::depictBoundingBox(cv::Mat & frame)
{
	cv::Mat frameWithRectangle;
	cv::namedWindow(boundingBoxPickerWindowName);
	cv::moveWindow(boundingBoxPickerWindowName, 10, 10);
	MouseCallbackDataStructure ms(0, 0, 0, 0);
	cvui::init(boundingBoxPickerWindowName);
	while (true) {

		frameWithRectangle = frame.clone();
		cv::setMouseCallback(boundingBoxPickerWindowName, mouseCallbackFunction, &ms);

		cvui::update();
		insertDetectedBoundingBoxes(frame);
		cv::rectangle(frameWithRectangle, ms.toRectangle(), cv::Scalar(0, 255, 0));
		cv::imshow(boundingBoxPickerWindowName, frameWithRectangle);
        int key = cv::waitKeyEx(30);
        if (key == 27) {
			break;
		} else if (key == 2555904) {
		    return cv::Rect(0, 0, -1, -1);
		} else if (key == 2424832) {
            backward_frame = true;
            return cv::Rect(0, 0, -1, -1);
        }
	}
	cv::setMouseCallback(boundingBoxPickerWindowName, nullptr, nullptr);
	return ms.toRectangle();
}

void Application::processFrame(cv::Mat & frame)
{
	if (frame.size().height == 0 | frame.size().width == 0) {
		exit(-1);
	}
    backward_frame = false;
    cv::Mat original_frame = frame.clone();
	while (true) {
		cv::Rect rect = depictBoundingBox(frame);
		if (!isRectangleValid(rect)) {
		    break;
		}
		std::string objectClass = pickClass();
		BoundingBox box(videoLoader->getVideoName(), videoLoader->getFrameNumber(), objectClass, rect);
		currentFrameBoundingBoxes.push_back(box);
        writer->writeBoundingBox(box, original_frame);
		if (!addAnotherObject) {
			break;
		}
	}
}

void Application::inicializeCategoryChecker()
{
	for (int i = 0; i < loader.getClasses().size(); i++) {
		categoryChecker.push_back(new bool(false));
	}
}

void Application::insertDetectedBoundingBoxes(cv::Mat &frame) {
	for (auto &box : currentFrameBoundingBoxes) {
		cv::Rect rect(box.x, box.y, box.width, box.height);
		cv::rectangle(frame, rect, cv::Scalar(0, 0, 255));
		cv::putText(frame, //target image
					box.objectClass, //text
					cv::Point(box.x, box.y - 5), //top-left position
					cv::FONT_HERSHEY_DUPLEX,
					0.5, // font-size
					CV_RGB(255, 0, 0), //font color
					1); // font width factor.
	}
}

bool Application::isRectangleValid(cv::Rect &rect) {
    return !(rect.height < 0 | rect.width < 0);
}


