#pragma once

#include <string>
#include "opencv2/opencv.hpp"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


class FrameLoader
{
public:
	FrameLoader(const std::string &videofile, int secondToStart, int stepSeconds);
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
	const unsigned int getFrameNumber() {
		return frameNumber;
	}
	const std::string &getVideoName() {
		return videoName;
	}

    int getFps() const;

    cv::Mat &getNextFrame();
private:
	cv::VideoCapture video;
	unsigned int frameNumber = 0;
	unsigned int numberOfFrames;
	int width;
	int height;
	int step;
	int fps;
	std::string videoName;
	const cv::Size PROCESSED_SIZE = cv::Size(1280, 720);
};

