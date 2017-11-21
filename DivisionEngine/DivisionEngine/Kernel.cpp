#include "Kernel.h"

namespace Division
{
	Kernel::Kernel()
	{

	}

	Kernel::~Kernel()
	{
		delete windowManager_;
	}

	void Kernel::initialize()
	{
		windowManager_ = new WindowManager();

		Window *wind = windowManager_->createWindow();

		// TODO: move following code to renderer
		MSG msg;
		while (wind->shouldContinue()) {

				//Clear render region with black
				LPDIRECT3DDEVICE9 pd3dDevice = wind->getDevice();
				pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

				//before rendering something, you have to call this
				pd3dDevice->BeginScene();

				//
				//rendering of scene objects happens her
				//

				//now end the scene          
				pd3dDevice->EndScene();

				//update screen = swap front and backbuffer
				pd3dDevice->Present(NULL, NULL, NULL, NULL);

				// A window has to handle its messages.
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
			}
	}
}