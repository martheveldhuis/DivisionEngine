#ifndef DIVISION_ENGINE
#define DIVISION_ENGINE

#include "ResourceManager.h"

class DivisionEngine
{
private:
	ResourceManager* rescourcemanger;

public:
	DivisionEngine();
	~DivisionEngine();

	ResourceManager* getRescourceManager();
};
#endif