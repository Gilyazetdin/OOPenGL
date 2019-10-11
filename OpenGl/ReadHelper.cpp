#include "ReadHelper.h"
#include <stdexcept>

long ReadHelper::getFileSize(const std::string& path)
{
	struct stat buff;
	stat(path.c_str(), &buff);

	return buff.st_size;
}

char* ReadHelper::readTo(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		throw std::runtime_error("File can not be opened!");
	}
	long size = getFileSize(path);
	char* out = new char[int(size) + 1];
	
	file.read(out, size);
	file.close();
	out[int(size)] = '\0';
	return out;
}