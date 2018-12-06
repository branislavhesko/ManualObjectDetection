#pragma once

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "cvui.h"
#include "ClassLoader.h"
#include "FrameLoader.h"


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
	FrameLoader *videoLoader;
	ClassLoader loader;
	WindowSize size = WindowSize(640, 480);
	std::vector<bool*> categoryChecker;
	const std::string classPickerFrameName = "Class picker";

	void inicializeCategoryChecker();
	std::string & pickClass();
	std::string & getPickedClassName();
	void depictBoundingBox();
};

