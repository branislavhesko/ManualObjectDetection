#pragma once

#include <string>
#include "opencv2/opencv.hpp"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


class LoadImagesFromVideo
{
public:
	LoadImagesFromVideo(const std::string &videofile, int secondToStart, int stepSeconds);
	LoadImagesFromVideo();
	~LoadImagesFromVideo();
	const int getWidth() const {
		return width;
	}
	const int getHeight() const {
		return height;
	}
	const std::string &getVideoName() const {
		return videoName;
	}
	const unsigned int getFrameNumber() const{
		return frameNumber;
	}
	const std::string &getVideoName() {
		return videoName;
	}

    int getStep() const;

    const void setPosition(unsigned int frame);

    int getFps() const;

    cv::Mat &getNextFrame();
    cv::Mat &getPreviousFrame();
private:
	cv::VideoCapture video;
	int frameNumber = 0;
	unsigned int numberOfFrames;
public:
    unsigned int getNumberOfFrames() const;

private:
    int width;
	int height;
	int step;
	int fps;
	std::string videoName;
	const cv::Size PROCESSED_SIZE = cv::Size(1280, 720);
};

