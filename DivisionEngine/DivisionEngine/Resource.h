#ifndef DIVISION_RESOURCE_H
#define DIVISION_RESOURCE_H

#include <string>

class Resource
{
private:
	std::string name_;

public:
	Resource();
	Resource(std::string);
	~Resource();
};
#endif
