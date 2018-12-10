#include "pch.h"
#include "FrameLoader.h"


FrameLoader::FrameLoader(const std::string &videofilename, int step)
{
	videoName = fs::path(videofilename).stem().string();
	std::cout << videoName << std::endl;
	video.open(videofilename);
	if (!video.isOpened()) {
		exit(-5116);
	}
	width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	height = video.get(CV_CAP_PROP_FRAME_HEIGHT);
	numberOfFrames = video.get(CV_CAP_PROP_FRAME_COUNT);
	this->step = step;
}

FrameLoader::FrameLoader()
{
}


FrameLoader::~FrameLoader()
{
	// delete video;
}

cv::Mat & FrameLoader::getNextFrame()
{
	static cv::Mat frame;
	static cv::Mat emptyFrame(0, 0, CV_8UC1);
	for (int i = 0; i < step; i++) {
		video >> frame;
		frameNumber++;
		if (frameNumber == numberOfFrames) {
			return emptyFrame;
		}
	}
	return frame;
}
