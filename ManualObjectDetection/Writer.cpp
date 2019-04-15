#include "pch.h"
#include "Writer.h"


Writer::Writer() = default;

Writer::~Writer() = default;

Writer::Writer(const std::string & filename)
{

	file.open(FILETOSAVE, std::fstream::app);
}

bool Writer::writeBoundingBox(const BoundingBox &box, const cv::Mat &image)
{
	if (!box.width || !box.height) {
		std::cout << "Invalid bounding box!" << std::endl;
		return false;
	}
	std::string line = box.filename + "\t" + std::to_string(box.frameNumber) + "\t" + box.objectClass + "\t" + std::to_string(box.x) + "\t"  +
			std::to_string(box.y) + "\t" + std::to_string(box.width) + "\t" + std::to_string(box.height) + "\n";
	std::cout << line << std::endl;
	file << line;

	cv::imwrite(PATH_TO_SAVE_IMAGES + box.filename + "_" + std::to_string(box.frameNumber) + ".png", image);
	return true;
}
