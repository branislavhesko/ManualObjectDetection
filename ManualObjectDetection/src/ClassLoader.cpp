#include "../include/pch.h"
#include "../include/ClassLoader.h"


ClassLoader::ClassLoader()
{
}


ClassLoader::~ClassLoader()
{
}

void ClassLoader::loadClasses()
{
	std::ifstream file;
	file.open(CLASSFILE);
	if (!file.is_open()) {
		std::cerr << "Error loading file" << std::endl;
		throw std::ios_base::failure("Class file could not be loaded!!!");
	}
	std::string entry;
	while (std::getline(file, entry)) {
		classes.push_back(entry);
	}
}
