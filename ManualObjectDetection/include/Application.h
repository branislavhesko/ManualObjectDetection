#pragma once

#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "cvui.h"
#include "ClassLoader.h"
#include "LoadImagesFromVideo.h"
#include "mouseCallback.h"
#include "Writer.h"
#include "LoadImagesFromDirectory.h"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


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
	explicit Application(WindowSize size);
	void run(const std::string &videoFilePath, int secondToStart, int step);
private:
	LoadImagesFromVideo *videoLoader;
	ClassLoader loader;
	WindowSize size = WindowSize(640, 480);
	std::vector<bool*> categoryChecker;
	std::vector<BoundingBox> currentFrameBoundingBoxes;
	bool addAnotherObject, endApplication=false;
    bool isRectangleValid(cv::Rect &);
	const std::string boundingBoxPickerWindowName = "Bounding box picker";
	const std::string classPickerFrameName = "Class picker";
	void processFrame(cv::Mat &frame);
	void inicializeCategoryChecker();
	void insertDetectedBoundingBoxes(cv::Mat &frame);
	std::string pickClass();
	std::string getPickedClassName();
	cv::Rect depictBoundingBox(cv::Mat & frame);
	Writer *writer;
	bool backward_frame = false;
};


