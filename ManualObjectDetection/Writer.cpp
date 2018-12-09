#include "pch.h"
#include "Writer.h"


Writer::Writer()
{
}


Writer::~Writer()
{
}

Writer::Writer(const std::string & filename)
{
	file.open(FILETOSAVE, std::ios::app);
}

bool Writer::writeBoundingBox(const BoundingBox & box)
{
	std::string line = box.filename + "\t" + box.objectClass + "\t" + std::to_string(box.x) + "\t" + 
		std::to_string(box.y) + "\t" + std::to_string(box.width) + "\t" + std::to_string(box.height) + "\n";
	std::cout << line << std::endl;
	file << line;
	return true;
}
