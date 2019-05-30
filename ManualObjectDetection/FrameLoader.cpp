#include "pch.h"
#include "FrameLoader.h"


FrameLoader::FrameLoader(const std::string &videofilename, int secondToStart, int stepSeconds)
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

FrameLoader::FrameLoader()=default;

FrameLoader::~FrameLoader()=default;

cv::Mat & FrameLoader::getNextFrame()
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

int FrameLoader::getFps() const {
    return fps;
}

cv::Mat &FrameLoader::getPreviousFrame() {
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
