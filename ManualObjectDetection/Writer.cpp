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
	std::fstream file;
	file.open(FILETOSAVE, std::ios::app);
}

bool Writer::writeBoundingBox(const BoundingBox & box)
{
	return false;
}
