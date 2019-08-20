#include "../include/pch.h"
#include "../include/Writer.h"


Writer::Writer() = default;

Writer::~Writer() = default;

Writer::Writer(const std::string & filename)
{
    time_program_started = get_time();
	file.open(FILETOSAVE, std::fstream::app);
}

bool Writer::writeBoundingBox(const BoundingBox &box, const cv::Mat &image)
{
	if (!box.width || !box.height) {
		std::cout << "Invalid bounding box!" << std::endl;
		return false;
	}
	std::string line = box.filename + "\t" + time_program_started + "\t" + std::to_string(box.frameNumber) + "\t" +
	        box.objectClass + "\t" + std::to_string(box.x) + "\t"  +
			std::to_string(box.y) + "\t" + std::to_string(box.width) + "\t" + std::to_string(box.height) + "\n";
	std::cout << line << std::endl;
	file << line;

	std::string image_path = PATH_TO_SAVE_IMAGES + box.filename + "_" +
	        std::to_string(box.frameNumber) + "_" + time_program_started + ".png";

	if (!fs::exists(image_path)) {
	    std::cout << "FILE: " << image_path << " does not exists!" << std::endl;
        cv::imwrite(image_path, image);
    }
	return true;
}

std::string Writer::get_time() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%d_%m_%y$%I_%M_%S",timeinfo);
    return std::string(buffer);
}
