// DivisionGame.cpp : Defines the entry point for the console application.
//
#include <iostream>

#include "Kernel.h"


int main()
{
	// This needs to be split into +/- 5 lines so the user can specify the needs
	Division::Kernel divisionEngine;
	divisionEngine.run();
	// 1. init engine
	// 2. specify window type
	// 3. specify renderer
	// 4. specify scene
	// 5. run engine


	return 0;
}