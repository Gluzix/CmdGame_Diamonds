#pragma once

#include <string>

class FileReader
{
public:
	FileReader(const std::string &filename);
	int getFileHeight();
	int getFileWidth();

private:
	std::string mFilename;
};

