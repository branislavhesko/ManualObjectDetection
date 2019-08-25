//
// Created by brani on 20.08.19.
//

#include "../include/LoadImagesFromDirectory.h"


void LoadImagesFromDirectory::loadImagesInPath() {
    for (auto &entry: fs::directory_iterator(path)) {
        std::cout  << entry << std::endl;
        images.push_back(entry);
    }
}

cv::Mat &LoadImagesFromDirectory::getPreviousFrame() {
    cv::Mat mat;
    return mat;
}

unsigned int LoadImagesFromDirectory::getNumberOfFrames() const {
    return 0;
}

unsigned int LoadImagesFromDirectory::getFrameNumber() const {
    return 0;
}

int LoadImagesFromDirectory::getStep() const {
    return 0;
}

unsigned int LoadImagesFromDirectory::getWidth() const {
    return LoadImages::getWidth();
}

unsigned int LoadImagesFromDirectory::getHeight() const {
    return LoadImages::getHeight();
}

const std::string &LoadImagesFromDirectory::getVideoName() const {
    return path;
}

const void LoadImagesFromDirectory::setPosition(unsigned frameNumber) {
    std::cout <<"TODO" <<std::endl;
}
