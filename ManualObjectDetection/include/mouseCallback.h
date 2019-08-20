#pragma once
#include "opencv2/opencv.hpp"

struct MouseCallbackDataStructure {
	int x;
	int y;
	int width;
	int height;
	bool leftButtonDown = false;
	bool rectangleIsDepicted = false;
	MouseCallbackDataStructure(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
	}
	cv::Rect toRectangle() {
		return cv::Rect(x, y, width, height);
	}
};


inline void mouseCallbackFunction(int event, int x, int y, int flag, void *param) {

	MouseCallbackDataStructure *ms = static_cast<MouseCallbackDataStructure *> (param);

	if (event == cv::EVENT_LBUTTONDOWN) {
		ms->x = x;
		ms->y = y;
		ms->width = 0;
		ms->height = 0;
		ms->leftButtonDown = true;
	}
	else if (event == cv::EVENT_LBUTTONUP) {
		ms->leftButtonDown = false;
		ms->rectangleIsDepicted = true;
		ms->width = x - ms->x;
		ms->height = y - ms->y;
	}
	else if (event == cv::EVENT_MOUSEMOVE) {
		if (ms->leftButtonDown) {
			ms->width = x - ms->x;
			ms->height = y - ms->y;
		}
	}
}
