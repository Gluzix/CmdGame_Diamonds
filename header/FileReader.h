#pragma once

#include <string>
#include <vector>

class FileReader
{
public:
	FileReader(const std::string& pathToFile);

	const std::vector<std::string> &getContent() const;
	void modifyContent(int y, int x, char ch);
	int getHeight() const;
	int getWidth() const;

private:
	std::vector<std::string> readFile{};
	int height{ 0 };
	int width{ 0 };
};
