#include "D3D9Renderer.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

namespace Division
{
	D3D9Renderer::D3D9Renderer(LPDIRECT3DDEVICE9 direct3DDevice)
		 : direct3DDevice_(direct3DDevice)
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


		// Turn off culling, so we see the front and back of the triangle
		direct3DDevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// Turn off D3D lighting, since we are providing our own vertex colors
		direct3DDevice_->SetRenderState(D3DRS_LIGHTING, FALSE);
		//direct3Ddevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		//direct3Ddevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
	}

	void D3D9Renderer::cleanup()
	{
		//TODO: only release when not in use?
		direct3DDevice_->Release();
		direct3DDevice_ = NULL;
	}

	void D3D9Renderer::setupMatrices()
	{
		D3DXMATRIXA16 matWorldRotY;
		D3DXMATRIXA16 matWorldScale;

		UINT iTime = GetTickCount64() % 1000; // replace with mouse move
		FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
		D3DXMatrixRotationY(&matWorldRotY, 0.5f * D3DX_PI);
		//D3DXMatrixScaling(&matWorldScale, .5, .5, .5);
	//	D3DXMatrixScaling(&matWorldScale, 5,5,5);
	//	matWorldRotY *= matWorldScale;
		direct3DDevice_->SetTransform(D3DTS_WORLD, &matWorldRotY);

		D3DXVECTOR3 vEyePt(0.0f, 8.0f, -5.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		direct3DDevice_->SetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
		direct3DDevice_->SetTransform(D3DTS_PROJECTION, &matProj);
	}

	void D3D9Renderer::setVertexBuffer(DivisionVertex * vertexBuffer, int verts)
	{
		// Create the vertex buffer.
		if (!vertexBuffer_ && FAILED(direct3DDevice_->CreateVertexBuffer(verts * sizeof(DivisionVertex),
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
		direct3DDevice_->SetStreamSource(0, vertexBuffer_, 0, sizeof(DivisionVertex));
	}

	void D3D9Renderer::setIndexBuffer(void* indexBuffer, int indexes)
	{
		// Create the vertex buffer.
		if (!indexBuffer_ && FAILED(direct3DDevice_->CreateIndexBuffer(indexes * sizeof(DWORD),
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
		direct3DDevice_->SetIndices(indexBuffer_);
	}

	void D3D9Renderer::setHandle(void *)
	{
	}

	void D3D9Renderer::setTexture(void* resource)
	{
		D3D9Texture* texture = static_cast<D3D9Texture*>(resource);
		direct3DDevice_->SetTexture(0, texture->getTextureData());
	}
	void D3D9Renderer::setHandle(void* handle)
	{
		windowHandle_ = static_cast<HWND>(handle);
	}
}