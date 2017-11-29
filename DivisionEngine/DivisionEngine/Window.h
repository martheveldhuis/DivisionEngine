#ifndef DIVISION_WINDOW_H
#define DIVISION_WINDOW_H

#include <Windows.h>
#include <d3d9.h>
namespace Division
{
	class Window
	{
	public:
		Window();
		~Window();
		static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		bool shouldContinue();
		LPDIRECT3DDEVICE9 getDevice();
	private:
		bool continue_;
		LPDIRECT3DDEVICE9 pd3dDevice; // TODO: rename both pd3ds
		LPDIRECT3D9 pD3D;
	};
}

#endif // !DIVISION_WINDOW_H