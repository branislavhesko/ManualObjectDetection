#pragma once

#include <string>
#include <fstream>

struct BoundingBox {
	std::string objectClass;
	int x;
	int y;
	int height;
	int width;
	BoundingBox(const std::string &object, int x, int y, int height, int width) {
		this->objectClass = object;
		this->x = x;
		this->y = y;
		this->height = height;
		this->width = width;
	}
};

class Writer
{
public:
	Writer();
	~Writer();
	Writer(const std::string &filename);
	bool writeBoundingBox(const BoundingBox &box);
};

