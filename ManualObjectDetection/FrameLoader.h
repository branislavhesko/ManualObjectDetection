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
	const std::string &getVideoName() const {
		return videoName;
	}
	cv::Mat &getNextFrame();
private:
	cv::VideoCapture video;
	int width;
	int height;
	int step;
	std::string videoName;
};

