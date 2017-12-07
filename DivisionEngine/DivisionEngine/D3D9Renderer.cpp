#include "D3D9Renderer.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace Division 
{
	LPDIRECT3D9 D3D9Renderer::direct3D_;
	LPDIRECT3DDEVICE9 D3D9Renderer::direct3Ddevice_;
	D3D9Renderer::D3D9Renderer()
	{
	}

	D3D9Renderer::~D3D9Renderer()
	{
	}

	void D3D9Renderer::setup()
	{
		initializeGraphics();
	}

	void D3D9Renderer::initializeGraphics()
	{
		//Create the Direct3D Object
		if (direct3D_ && direct3Ddevice_)
			return;

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
		D3DXMATRIXA16 matWorldRotY;
	    D3DXMATRIXA16 matWorldScale;

		UINT iTime = GetTickCount64() % 1000; // replace with mouse move
		FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
		D3DXMatrixRotationY(&matWorldRotY, fAngle);
		//D3DXMatrixScaling(&matWorldScale, .5, .5, .5);
	//	D3DXMatrixScaling(&matWorldScale, 5,5,5);
	//	matWorldRotY *= matWorldScale;
		direct3Ddevice_->SetTransform(D3DTS_WORLD, &matWorldRotY);

		D3DXVECTOR3 vEyePt(0.0f, 8.0f, -5.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);// add position to the view.
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		direct3Ddevice_->SetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 300.0f);
		direct3Ddevice_->SetTransform(D3DTS_PROJECTION, &matProj);
	}

	void D3D9Renderer::setVertexBuffer(DivisionVertex * vertexBuffer, int verts)
	{
		// Create the vertex buffer.
		if (!vertexBuffer_ && FAILED(direct3Ddevice_->CreateVertexBuffer(verts * sizeof(DivisionVertex),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &vertexBuffer_, NULL)))
		{
			;
		}

		// Fill the vertex buffer.
		VOID* pVertices;
		if (FAILED(vertexBuffer_->Lock(0, sizeof(DivisionVertex) * verts, (void**)&pVertices, 0)))
			;
		memcpy(pVertices, vertexBuffer, sizeof(DivisionVertex) * verts);
		vertexBuffer_->Unlock();
		direct3Ddevice_->SetStreamSource(0, vertexBuffer_, 0, sizeof(DivisionVertex));
	}

	void D3D9Renderer::setIndexBuffer(void* indexBuffer, int indexes)
	{
		// Create the vertex buffer.
		if (!indexBuffer_ && FAILED(direct3Ddevice_->CreateIndexBuffer(indexes * sizeof(DWORD),
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
		direct3Ddevice_->SetIndices(indexBuffer_);
	}



	void D3D9Renderer::setTexture(void* resource)
	{
		D3D9Texture* texture = static_cast<D3D9Texture*>(resource);
		direct3Ddevice_->SetTexture(0, texture->getTextureData());
	}
	void D3D9Renderer::setHandle(void* handle)
	{
		windowHandle_ = static_cast<HWND>(handle);
	}
}