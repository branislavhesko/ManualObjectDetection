#pragma once

#include <string>
#include <iostream>
#include <fstream>

struct BoundingBox {
	std::string filename;
	std::string objectClass;
	int x;
	int y;
	int height;
	int width;
	BoundingBox(const std::string &filename, std::string &object, int x, int y, int height, int width) {
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
private:
	const std::string FILETOSAVE = "./detected.txt";
	std::fstream file;
};

