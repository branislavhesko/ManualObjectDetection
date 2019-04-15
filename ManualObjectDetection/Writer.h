#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"

struct BoundingBox {
	std::string filename;
	std::string objectClass;
	int x;
	int y;
	int height;
	int width;
	int frameNumber;
	BoundingBox(const std::string &filename, int frameNumber, const std::string &object, int x, int y, int height, int width) {
		this->objectClass = object;
		this->x = x;
		this->y = y;
		this->height = height;
		this->width = width;
		this->filename = filename;
		this->frameNumber = frameNumber;
	}
	BoundingBox(const std::string &filename, int frameNumber, const std::string &object, const cv::Rect &rect) {
		this->objectClass = object;
		this->x = rect.x;
		this->y = rect.y;
		this->height = rect.height;
		this->width = rect.width;
		this->filename = filename;
		this->frameNumber = frameNumber;
	}
};

class Writer
{
public:
	Writer();
	~Writer();
	explicit Writer(const std::string &filename);
	bool writeBoundingBox(const BoundingBox &box, const cv::Mat &image);
private:
	const std::string FILETOSAVE = "./detected.txt";
	std::fstream file;
	const std::string PATH_TO_SAVE_IMAGES = "./images/";
};

