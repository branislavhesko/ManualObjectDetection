#include "../include/pch.h"
#include "../include/LoadImagesFromVideo.h"


LoadImagesFromVideo::LoadImagesFromVideo(const std::string &videofilename, int secondToStart, int stepSeconds)
{
	videoName = fs::path(videofilename).stem().string();
	std::cout << videoName << std::endl;
	video.open(videofilename);
	if (!video.isOpened()) {
		exit(-5116);
	}
	width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
	height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
	numberOfFrames = (int)video.get(cv::CAP_PROP_FRAME_COUNT);
	fps = (int)video.get(cv::CAP_PROP_FPS);
	video.set(cv::CAP_PROP_POS_FRAMES, secondToStart * fps);
	this->step = stepSeconds * int(fps);
}

LoadImagesFromVideo::LoadImagesFromVideo()=default;

LoadImagesFromVideo::~LoadImagesFromVideo()=default;

cv::Mat & LoadImagesFromVideo::getNextFrame()
{
	static cv::Mat frame;
	static cv::Mat emptyFrame(0, 0, CV_8UC1);
	frameNumber += step;
    if (frameNumber > numberOfFrames) {
        return emptyFrame;
    }
    video.set(cv::CAP_PROP_POS_FRAMES, frameNumber);
    video >> frame;
	cv::resize(frame, frame, PROCESSED_SIZE);
	return frame;
}

int LoadImagesFromVideo::getFps() const {
    return fps;
}

cv::Mat &LoadImagesFromVideo::getPreviousFrame() {
    static cv::Mat frame;
    frameNumber -= step;

    if (frameNumber < 0) {
        frameNumber = 0;
    }
    video.set(cv::CAP_PROP_POS_FRAMES, frameNumber);
    video >> frame;
    cv::resize(frame, frame, PROCESSED_SIZE);
    return frame;
}

const void LoadImagesFromVideo::setPosition(unsigned int frameNumberToSet) {
    if (frameNumberToSet > numberOfFrames)
    {
        frameNumberToSet = 0;
    }
    frameNumber = frameNumberToSet;
    video.set(cv::CAP_PROP_POS_FRAMES, frameNumberToSet);
}

unsigned int LoadImagesFromVideo::getNumberOfFrames() const {
    return numberOfFrames;
}

int LoadImagesFromVideo::getStep() const {
    return step;
}
