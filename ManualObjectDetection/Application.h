#pragma once

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "cvui.h"
#include "ClassLoader.h"
#include "FrameLoader.h"
#include "mouseCallback.h"
#include "Writer.h"

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
	void run(const std::string &videoFilePath, int secondToStart, int step);
private:
	FrameLoader *videoLoader;
	ClassLoader loader;
	WindowSize size = WindowSize(640, 480);
	std::vector<bool*> categoryChecker;
	std::vector<BoundingBox> currentFrameBoundingBoxes;
	bool addAnotherObject, endApplication=false;

	const std::string boundingBoxPickerWindowName = "Bounding box picker";
	const std::string classPickerFrameName = "Class picker";
	void processFrame(cv::Mat &frame);
	void inicializeCategoryChecker();
	void insertDetectedBoundingBoxes(cv::Mat &frame);
	std::string & pickClass();
	std::string & getPickedClassName();
	cv::Rect depictBoundingBox(cv::Mat & frame);
	Writer *writer;
};


