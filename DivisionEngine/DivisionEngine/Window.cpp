#include "Window.h"


// define the screen resolution
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

namespace Division
{
	//Besides the main function, there must be a message processing function
	LRESULT WINAPI Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	bool Window::shouldContinue()
	{
		return continue_;
	}

	LPDIRECT3DDEVICE9 Window::getDevice()
	{
		return pd3dDevice;
	}

	Window::Window()
	{
		continue_ = true;

		//Create a window class.
		WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, NULL, 0L, 0L,
			GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
			"Direct3D Window", NULL };
		wc.lpfnWndProc = Window::MsgProc;

		//Register the window class.
		RegisterClassEx(&wc);

		//Create the application's window.
		HWND hWnd = CreateWindow("Direct3D Window", "DirectXers - D3D9 Tutorial 1",
			WS_EX_TOPMOST | WS_POPUP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
			GetDesktopWindow(), NULL, wc.hInstance, NULL);

		ShowWindow(hWnd, SW_SHOW);

		//Create the Direct3D Object
		pD3D = NULL;
		if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
			; //log failure

		//Setup the device presentation parameters
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
		d3dpp.BackBufferWidth = SCREEN_WIDTH;    // set the width of the buffer
		d3dpp.BackBufferHeight = SCREEN_HEIGHT;    // set the height of the buffer

												   //The final step is to use the IDirect3D9::CreateDevice method to create the Direct3D device, as illustrated in the
												   //following code example.
		pd3dDevice = NULL;
		if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp, &pd3dDevice)))
		{
			MessageBox(hWnd, "No HAL HARDWARE_VERTEXPROCESSING! Sample will exit!", NULL, 0);
			pD3D->Release();
			pD3D = NULL;
			; //log failure
		}
	}


	Window::~Window()
	{
		//Do not forget to clean up here
		pd3dDevice->Release();
		pd3dDevice = NULL;
		pD3D->Release();
		pD3D = NULL;
	}
}