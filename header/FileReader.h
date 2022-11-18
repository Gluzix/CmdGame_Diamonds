#pragma once

#include <string>
#include <vector>

class FileReader
{
public:
	FileReader(const std::string& pathToFile);

	const std::vector<std::string> &getContent() const;
	int getHeight() const;
	int getWidth() const;

private:
	std::vector<std::string> readFile{};
	int height{ 0 };
	int width{ 0 };
};
