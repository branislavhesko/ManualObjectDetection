#include "pch.h"
#include "FrameLoader.h"


FrameLoader::FrameLoader(const std::string &videofilename, int step)
{
	video.open(videofilename);
	if (!video.isOpened()) {
		exit(-5116);
	}
	width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	height = video.get(CV_CAP_PROP_FRAME_HEIGHT);
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
	for (int i = 0; i < step; i++) {
		video >> frame;
	}
	return frame;
}
