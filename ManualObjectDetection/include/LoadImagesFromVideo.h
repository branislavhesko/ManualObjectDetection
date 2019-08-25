#pragma once

#include <string>
#include "opencv2/opencv.hpp"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "LoadImages.h"


class LoadImagesFromVideo: public LoadImages
{
public:
	LoadImagesFromVideo(std::string &videofilename, int secondToStart, int stepSeconds);
	~LoadImagesFromVideo();
	unsigned getWidth() const {
		return width;
	}
	unsigned getHeight() const {
		return height;
	}
	const std::string &getVideoName() const {
		return path;
	}

    unsigned getFrameNumber() const{
		return frameNumber;
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
	unsigned step;
	unsigned fps;
	const cv::Size PROCESSED_SIZE = cv::Size(1280, 720);
};

