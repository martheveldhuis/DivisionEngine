#ifndef DIVISION_DIVISIONENGINE_H
#define DIVISION_DIVISIONENGINE_H

#include "ResourceManager.h"

class DivisionEngine
{
private:
	ResourceManager* resourceManager_;

public:
	DivisionEngine();
	~DivisionEngine();

	ResourceManager* getResourceManager();
};
#endif