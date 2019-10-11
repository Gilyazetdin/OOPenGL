#pragma once

#include <string>
#include <fstream>

class ReadHelper
{
public:
	static long getFileSize(const std::string& path);
	static char* readTo(const std::string& path);
private:
	ReadHelper() {}
};

