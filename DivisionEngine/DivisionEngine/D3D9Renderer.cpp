#include "D3D9Renderer.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace Division 
{

	D3D9Renderer::D3D9Renderer(LPDIRECT3D9 direct3D, LPDIRECT3DDEVICE9 direct3Ddevice, HWND windowHandle) :
		direct3D_(direct3D), direct3Ddevice_(direct3Ddevice), windowHandle_(windowHandle)
	{
		setup();
	}

	D3D9Renderer::~D3D9Renderer()
	{
	}

	void D3D9Renderer::render(int vertices, int indices)
	{
		// Clear the backbuffer to a black color
		direct3Ddevice_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0xff, 0xff), 1.0f, 0);

		HRESULT a = direct3Ddevice_->BeginScene();
		// Begin the scene
		if (SUCCEEDED(a))
		{
			// Setup the world, view, and projection matrices
			setupMatrices();

			// Render the vertex buffer contents
			direct3Ddevice_->SetStreamSource(0, vertexBuffer_, 0, sizeof(CUSTOMVERTEX));
			direct3Ddevice_->SetFVF(D3DFVF_CUSTOMVERTEX);
			direct3Ddevice_->SetIndices(indexBuffer_);
			direct3Ddevice_->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, vertices, 0, indices - 2);
			//direct3Ddevice_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 9997);

			// End the scene
			direct3Ddevice_->EndScene();
		}

		// Present the backbuffer contents to the display
		direct3Ddevice_->Present(NULL, NULL, NULL, NULL);
	}


	void D3D9Renderer::setup()
	{
		initGraphics();
	}

	void D3D9Renderer::initGraphics()
	{
		//Create the Direct3D Object
		direct3D_ = NULL;
		if (NULL == (direct3D_ = Direct3DCreate9(D3D_SDK_VERSION)))
			; //log failure

			  //Setup the device presentation parameters
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		//d3dpp.BackBufferWidth = SCREEN_WIDTH;    // set the width of the buffer
		//d3dpp.BackBufferHeight = SCREEN_HEIGHT;    // set the height of the buffer

		//The final step is to use the IDirect3D9::CreateDevice method to create the Direct3D device, as illustrated in the
		//following code example.

		direct3Ddevice_ = NULL;
		if (FAILED(direct3D_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle_,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &direct3Ddevice_)))
		{
			MessageBox(windowHandle_, "No HAL software_VERTEXPROCESSING! will exit!", NULL, 0);
			direct3D_->Release();
			direct3D_ = NULL;
			; //log failure
		}

		// Turn off culling, so we see the front and back of the triangle
		direct3Ddevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// Turn off D3D lighting, since we are providing our own vertex colors
		direct3Ddevice_->SetRenderState(D3DRS_LIGHTING, FALSE);
		//direct3Ddevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		//direct3Ddevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
	}

	void D3D9Renderer::cleanup()
	{
		//TODO: only release when not in use?
		direct3Ddevice_->Release();
		direct3Ddevice_ = NULL;
		direct3D_->Release();
		direct3D_ = NULL;
	}

	void D3D9Renderer::setupMatrices()
	{
		// For our world matrix, we will just rotate the object about the y-axis.
		D3DXMATRIXA16 matWorld;

		// Set up the rotation matrix to generate 1 full rotation (2*PI radians)
		// every 1000 ms. To avoid the loss of precision inherent in very high
		// floating point numbers, the system time is modulated by the rotation
		// period before conversion to a radian angle.
		UINT iTime = GetTickCount64() % 1000; // replace with mouse move
		FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
		D3DXMatrixRotationY(&matWorld, 0);
		direct3Ddevice_->SetTransform(D3DTS_WORLD, &matWorld);

		// Set up our view matrix. A view matrix can be defined given an eye point,
		// a point to lookat, and a direction for which way is up. Here, we set the
		// eye five units back along the z-axis and up three units, look at the
		// origin, and define "up" to be in the y-direction.
		D3DXVECTOR3 vEyePt(0.0f, 13.0f, -15.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 10.0f);// add position to the view.
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		direct3Ddevice_->SetTransform(D3DTS_VIEW, &matView);

		// For the projection matrix, we set up a perspective transform (which
		// transforms geometry from 3D view space to 2D viewport space, with
		// a perspective divide making objects smaller in the distance). To build
		// a perpsective transform, we need the field of view (1/4 pi is common),
		// the aspect ratio, and the near and far clipping planes (which define at
		// what distances geometry should be no longer be rendered).
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
		direct3Ddevice_->SetTransform(D3DTS_PROJECTION, &matProj);
	}

	void D3D9Renderer::setVertexBuffer(CUSTOMVERTEX * vertexBuffer, int verts)
	{
		// Create the vertex buffer.
		if (FAILED(direct3Ddevice_->CreateVertexBuffer(verts * sizeof(CUSTOMVERTEX),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &vertexBuffer_, NULL)))
		{
			;
		}

		// Fill the vertex buffer.
		VOID* pVertices;
		if (FAILED(vertexBuffer_->Lock(0, sizeof(CUSTOMVERTEX) * verts, (void**)&pVertices, 0)))
			;
		memcpy(pVertices, vertexBuffer, sizeof(CUSTOMVERTEX) * verts);
		vertexBuffer_->Unlock();
	}

	void D3D9Renderer::setIndexBuffer(void* indexBuffer, int indexes)
	{
		// Create the vertex buffer.
		if (FAILED(direct3Ddevice_->CreateIndexBuffer(indexes * sizeof(DWORD),
			D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
			D3DFMT_INDEX32,
			D3DPOOL_DEFAULT, &indexBuffer_, NULL)))
		{
			;
		}

		// Fill the vertex buffer.
		VOID* pData;
		if (FAILED(indexBuffer_->Lock(0, sizeof(DWORD) * indexes, (void**)&pData, 0)))
			;
		memcpy(pData, indexBuffer, sizeof(DWORD) * indexes);
		vertexBuffer_->Unlock();
	}
}