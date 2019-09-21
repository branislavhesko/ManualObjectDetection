#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class ClassLoader
{
public:
	ClassLoader();
	~ClassLoader();
	void loadClasses();
	const std::vector<std::string> &getClasses() const {
		return classes;
	}
private:
	const std::string CLASSFILE = "./classes.txt";
	std::vector<std::string> classes;
};

