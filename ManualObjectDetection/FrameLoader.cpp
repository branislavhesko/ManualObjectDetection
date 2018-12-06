#include "pch.h"
#include "FrameLoader.h"


FrameLoader::FrameLoader(const std::string &videofilename, int step)
{
	video = new cv::VideoCapture(videofilename);
	width = video->get(CV_CAP_PROP_FRAME_WIDTH);
	height = video->get(CV_CAP_PROP_FRAME_HEIGHT);
	this->step = step;
}

FrameLoader::FrameLoader()
{
}


FrameLoader::~FrameLoader()
{
	delete video;
}

cv::Mat & FrameLoader::getNextFrame()
{
	cv::Mat frame;
	for (int i = 0; i < step; i++) {
	*video >> frame;
	}
	return frame;
}
