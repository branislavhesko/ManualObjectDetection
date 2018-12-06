#pragma once

#include <string>
#include "opencv2/opencv.hpp"

class FrameLoader
{
public:
	FrameLoader(const std::string &videofile, int step);
	FrameLoader();
	~FrameLoader();
	const int getWidth() const {
		return width;
	}
	const int getHeight() const {
		return height;
	}
	cv::Mat &getNextFrame();
private:
	cv::VideoCapture *video;
	int width;
	int height;
	int step;
};

