#ifndef RESOURCE
#define RESOURCE

#include <string>

class Resource
{
private:
	std::string name;

public:
	Resource();
	Resource(std::string);
	~Resource();
};
#endif
