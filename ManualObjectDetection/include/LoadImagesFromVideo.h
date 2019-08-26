#pragma once

#include <string>
#include "opencv2/opencv.hpp"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "LoadImages.h"


class LoadImagesFromVideo: public LoadImages {
public:
	LoadImagesFromVideo(std::string &videofilename, int secondToStart, int stepSeconds);
	~LoadImagesFromVideo();
	unsigned getWidth() const override {
		return width;
	}
	unsigned getHeight() const override{
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
public:
    unsigned int getNumberOfFrames() const;

private:
	unsigned step;
	unsigned fps;
};

