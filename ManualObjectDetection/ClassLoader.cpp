#include "pch.h"
#include "ClassLoader.h"


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
		throw std::ios_base::failure("File not loaded");
	}
	std::string entry;
	while (std::getline(file, entry)) {
		classes.push_back(entry);
	}
}
