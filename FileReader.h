#pragma once

#include <string>

class FileReader
{
public:
	FileReader(const std::string &filename);

	int getFileHeight() const;
	int getFileWidth() const;

private:
	std::string mFilename;
};

