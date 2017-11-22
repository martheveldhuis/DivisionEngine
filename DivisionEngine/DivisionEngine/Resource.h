#ifndef RESOURCE
#define RESOURCE
#include<string>

class Resource
{
private:
	std::string name;

public:
	Resource();
	Resource(std::string);
	~Resource();
	friend bool operator==(Resource* l, std::string r) {
		return l->getName() == r;
	}
	friend bool operator==(std::string r, Resource* l) {
		return l->getName() == r;
	}

	std::string getName();
};
#endif
