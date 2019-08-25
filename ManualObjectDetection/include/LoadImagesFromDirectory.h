//
// Created by brani on 20.08.19.
//

#ifndef MANUALOBJECTDETECTION_LOADIMAGESFROMDIRECTORY_H
#define MANUALOBJECTDETECTION_LOADIMAGESFROMDIRECTORY_H

#include <string>
#include <vector>
#include "LoadImages.h"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

class LoadImagesFromDirectory: public LoadImages {
public:
    explicit LoadImagesFromDirectory(std::string &path) : LoadImages(path) {
        loadImagesInPath();
    }
    cv::Mat& getNextFrame() override {
        cv::Mat mat;
        return mat;
    }

    cv::Mat &getPreviousFrame() override;

    unsigned int getNumberOfFrames() const override;

    unsigned int getFrameNumber() const override;

    int getStep() const override;

    unsigned int getWidth() const override;

    unsigned int getHeight() const override;

    const std::string &getVideoName() const override;

    const void setPosition(unsigned frameNumber) override;

private:
    void loadImagesInPath();

    std::vector<fs::path> images;
};


#endif //MANUALOBJECTDETECTION_LOADIMAGESFROMDIRECTORY_H
