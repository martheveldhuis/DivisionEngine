// DivisionGame.cpp : Defines the entry point for the console application.
//
#include "DivisionEngine.h"
#include <iostream>

int main()
{
	DivisionEngine Engine;
	ResourceManager* ResourceManger;

	ResourceManger = Engine.getRescourceManager();

	ResourceManger->createResource("Stone");

	Resource* test = ResourceManger->getResource("Stone");

	while (true) {
	}

	return 0;
}