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
}

Application::Application(const WindowSize size)
{

}

void Application::run(const std::string & videoFilePath)
{
	loader.loadClasses();
	inicializeCategoryChecker();
	frame = cv::Mat((1 + loader.getClasses().size()) * 100, 400, CV_8UC3);
	cv::namedWindow(classPickerFrameName);
	cv::moveWindow(classPickerFrameName, 1000, 100);
	cvui::init(classPickerFrameName);
	cvui::watch(classPickerFrameName);
	bool value = false;
	while (true) {
		// TODO: repair this ...
		getClassFrame();
		cvui::update();
		// Show everything on the screen
		cv::imshow(classPickerFrameName, frame);
		// Check if ESC key was pressed
		if (cv::waitKey(20) == 27) {
			break;
		}
	}
}

void Application::getClassFrame()
{
	unsigned int size = loader.getClasses().size();
	frame = cv::Scalar(49, 52, 49);
	int i = 0;
	for (auto entry : loader.getClasses()) {
		cvui::checkbox(frame, 50, i * 100 + 50, entry, categoryChecker[i]);
		i++;
	}
	if (cvui::button(frame, 50, i * 100 + 50, "PRESS OK")) {
	
	}

}

void Application::inicializeCategoryChecker()
{
	for (int i = 0; i < loader.getClasses().size(); i++) {
		categoryChecker.push_back(new bool(false));
	}
}
