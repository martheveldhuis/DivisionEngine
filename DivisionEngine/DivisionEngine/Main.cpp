#include <Windows.h>
#include <d3d9.h>
#include "LoggerPool.h"
#include "Kernel.h"


bool g_bContinue = true;

//Besides the main function, there must be a message processing function
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		g_bContinue = false;
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//The entry point of a windows application is the WinMain function
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	Division::Kernel* DivisionKernel = new Division::Kernel();
	DivisionKernel->initialize();
	return 0;
}