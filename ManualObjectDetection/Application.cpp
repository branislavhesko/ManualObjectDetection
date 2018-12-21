#include "pch.h"
#include "Application.h"


Application::Application()
{
}


Application::~Application()
{
	for (auto *flag : categoryChecker) {
		delete flag;
	}
	delete videoLoader;
}

Application::Application(const WindowSize size)
{

}

void Application::run(const std::string & videoFilePath, int secondToStart, int step)
{
	videoLoader = new FrameLoader(videoFilePath, secondToStart, step);
	loader.loadClasses();
	writer = new Writer("./detected.csv");
	inicializeCategoryChecker();
	while (!endApplication) {
		processFrame(videoLoader->getNextFrame());
	}
	delete writer;

}

std::string & Application::pickClass()
{
	cv::namedWindow(classPickerFrameName);
	cv::moveWindow(classPickerFrameName, 1000, 100);
	cvui::init(classPickerFrameName);
	cvui::watch(classPickerFrameName);
	cv::Mat frame = cv::Mat((2 + loader.getClasses().size()) * 100, 400, CV_8UC3);
	addAnotherObject = false;
	while (true) {
		unsigned int size = loader.getClasses().size();
		frame = cv::Scalar(49, 52, 49);
		int i = 0;
		for (const auto &entry : loader.getClasses()) {
			cvui::checkbox(frame, 50, i * 100 + 50, entry, categoryChecker[i]);
			i++;
		}
		if (cvui::button(frame, 220, i * 100 + 50, "ALL OBJECTS FOUND")) {
			break;
		}
		if (cvui::button(frame, 50, i * 100 + 50, "ADD ANOTHER")) {
			addAnotherObject = true;
			break;
		}
		if (cvui::button(frame, 50, (i +1 ) * 100 + 50, "END APPLICATION")) {
			endApplication = true;
			break;
		}
		cvui::update();
		// Show everything on the screen
		cv::imshow(classPickerFrameName, frame);
		// Check if ESC key was pressed
		if (cv::waitKey(20) == 27) {
			break;
		}
	}
	cv::destroyWindow(classPickerFrameName);
	return getPickedClassName();
}

std::string & Application::getPickedClassName()
{
	static std::string pickedClass = "None";
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
	cv::moveWindow(boundingBoxPickerWindowName, 100, 100);
	MouseCallbackDataStructure ms(0, 0, 0, 0);
	cvui::init(boundingBoxPickerWindowName);
	while (true) {

		frameWithRectangle = frame.clone();
		cv::setMouseCallback(boundingBoxPickerWindowName, mouseCallbackFunction, &ms);

		cvui::update();
		cv::rectangle(frameWithRectangle, ms.toRectangle(), cv::Scalar(0, 255, 0));
		cv::imshow(boundingBoxPickerWindowName, frameWithRectangle);
		if (cv::waitKey(30) == 27) {
			break;
		}
	}
	return ms.toRectangle();
}

void Application::processFrame(cv::Mat & frame)
{
	if (frame.size().height == 0 | frame.size().width == 0) {
		exit(-1);
	}
	while (true) {
		cv::Rect rect = depictBoundingBox(frame);
		std::string objectClass = pickClass();
		writer->writeBoundingBox(BoundingBox(videoLoader->getVideoName(), videoLoader->getFrameNumber(), objectClass, rect));
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


