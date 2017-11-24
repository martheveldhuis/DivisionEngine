#include <Windows.h>
#include <d3d9.h>

#include "Logger.h"
#include "Kernel.h"

//The entry point of a windows application is the WinMain function
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	// Test the logger
	Division::Logger* logger = new Division::Logger();
	logger->logError("I am an error");
	logger->logWarning("I am a warning");
	logger->logInfo("I am an info message");
	delete logger;

	Division::Kernel* DivisionKernel = new Division::Kernel();
	DivisionKernel->initialize();
	return 0;
}