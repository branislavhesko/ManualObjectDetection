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
	BoundingBox(const std::string &filename, const std::string &object, int x, int y, int height, int width) {
		this->objectClass = object;
		this->x = x;
		this->y = y;
		this->height = height;
		this->width = width;
		this->filename = filename;
	}
	BoundingBox(const std::string &filename, const std::string &object, const cv::Rect &rect) {
		this->objectClass = object;
		this->x = rect.x;
		this->y = rect.y;
		this->height = rect.height;
		this->width = rect.width;
		this->filename = filename;
	}
};

class Writer
{
public:
	Writer();
	~Writer();
	Writer(const std::string &filename);
	bool writeBoundingBox(const BoundingBox &box);
private:
	const std::string FILETOSAVE = "./detected.txt";
	std::fstream file;
};

