#pragma once

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "cvui.h"
#include "ClassLoader.h"


struct WindowSize {
	unsigned int width;
	unsigned int height;
	WindowSize(unsigned int x, unsigned int y) {
		this->width = x;
		this->height = y;
	}
};

class Application
{
public:
	Application();
	~Application();
	Application(const WindowSize size);
	void run(const std::string &videoFilePath);

private:
	ClassLoader loader;
	WindowSize size = WindowSize(640, 480);
	void getClassFrame();
	std::vector<bool*> categoryChecker;
	const std::string classPickerFrameName = "Class picker";
	cv::Mat frame;
	void inicializeCategoryChecker();
};

