//
// Created by brani on 20.08.19.
//

#ifndef MANUALOBJECTDETECTION_LOADIMAGES_H
#define MANUALOBJECTDETECTION_LOADIMAGES_H

#include "opencv2/opencv.hpp"
#include <string>


class LoadImages {
public:
    explicit LoadImages(std::string &path) : path(path) {};
    virtual cv::Mat& getNextFrame() = 0;
    virtual cv::Mat& getPreviousFrame() = 0;
    virtual unsigned getNumberOfFrames() const = 0;
    virtual unsigned getFrameNumber() const = 0;
    virtual int getStep() const = 0;
    virtual unsigned getWidth() const {
        return this->width;
    };
    virtual unsigned getHeight() const {
        return this->height;
    }

    virtual const std::string &getVideoName() const = 0;
    virtual const void setPosition(unsigned frameNumber) = 0;


protected:
    std::string path;
    unsigned width;
    unsigned height;
};


#endif //MANUALOBJECTDETECTION_LOADIMAGES_H
