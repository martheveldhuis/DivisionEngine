#include "DivisionEngine.h"

DivisionEngine::DivisionEngine()
{
	rescourcemanger = new ResourceManager();
}

DivisionEngine::~DivisionEngine()
{
}

ResourceManager * DivisionEngine::getRescourceManager()
{
	return rescourcemanger;
}