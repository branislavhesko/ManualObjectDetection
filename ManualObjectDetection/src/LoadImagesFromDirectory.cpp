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
    static cv::Mat img;
    img = cv::imread(images[frameNumber]);
    cv::resize(img, img, PROCESSED_SIZE);
    if (--frameNumber < 0) {
        frameNumber = getNumberOfFrames() - 1;
    }
    return img;
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
    static std::string imgName;
    imgName = fs::path(images[frameNumber]).stem();
    return imgName;
}

const void LoadImagesFromDirectory::setPosition(unsigned frameNumber) {
    this->frameNumber = frameNumber;
}

void LoadImagesFromDirectory::determineImagesDimensions() {
    cv::Mat img = cv::imread(images[0]);
    width = img.cols;
    height = img.rows;
}

cv::Mat &LoadImagesFromDirectory::getNextFrame() {
        static cv::Mat img;
        img = cv::imread(images[frameNumber]);
        cv::resize(img, img, PROCESSED_SIZE);
        if (++frameNumber == getNumberOfFrames()) {
            frameNumber = 0;
        }
        return img;
}
