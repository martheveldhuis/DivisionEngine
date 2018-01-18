#include "D3D9Renderer.h"
#include "D3D9Texture.h"
#include <d3dx9.h>
#include <math.h>
#include "D3D9Camera.h"
#include "LoggerPool.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

namespace Division
{
	D3D9Renderer::D3D9Renderer(LPDIRECT3DDEVICE9 direct3DDevice) :
		direct3DDevice_(direct3DDevice)
	{
	}



	D3D9Renderer::~D3D9Renderer()
	{
	}



	void D3D9Renderer::setup()
	{
		initializeGraphics();
		setupMatrices();

		direct3DDevice_->SetFVF(D3DFVF_CUSTOMVERTEX);
	}



	void D3D9Renderer::initializeGraphics()
	{
		direct3DDevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		direct3DDevice_->SetRenderState(D3DRS_LIGHTING, FALSE);
		//direct3DDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}



	void D3D9Renderer::setupMatrices()
	{
		D3DXVECTOR3 viewPointStart(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 viewLookAt(5.0f, -1.0f, 0.0f);
		D3DXVECTOR3 upVector(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 viewMatrix;
		D3DXMatrixLookAtLH(&viewMatrix, &viewPointStart, &viewLookAt, &upVector);
		direct3DDevice_->SetTransform(D3DTS_VIEW, &viewMatrix);

		D3DXMATRIXA16 projectionMatrix;
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, 1.0f, 0.4f, 100.0f);
		direct3DDevice_->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
	}

	void D3D9Renderer::setCameraMatrix(void* view)
	{
		cameraView_ = static_cast<D3DXMATRIX*>(view);
	}



	void D3D9Renderer::setWorldMatrix(Position* position)
	{
		D3DXMATRIX translationEntity;
		D3DXMATRIX rotationEntity;
		D3DXMATRIX worldEntity;
		
		// Translate and rotate the entity into the world.
		D3DXMatrixTranslation(&translationEntity, position->xPosition, 
							  position->yPosition, position->zPosition);
		D3DXMatrixRotationYawPitchRoll(&rotationEntity, position->yAngle, 
									   position->xAngle, position->zAngle);
		// Translate then rotate, so the entity is rendered on the right spot.
		D3DXMatrixMultiply(&worldEntity, &translationEntity, &rotationEntity);

		direct3DDevice_->SetTransform(D3DTS_WORLD, &(worldEntity * (*cameraView_)));
	}



	void D3D9Renderer::setVertexBuffer(DivisionVertex* vertexBuffer, int verts)
	{
		// Create the vertex buffer.
		if (FAILED(direct3DDevice_->CreateVertexBuffer(verts * sizeof(DivisionVertex),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &vertexBuffer_, NULL)))
		{
			;
		}

		// Fill the vertex buffer.
		VOID* pVertices;
		if (FAILED(vertexBuffer_->Lock(0, sizeof(DivisionVertex)* verts, (void**)&pVertices, 0)))
			;
		memcpy(pVertices, vertexBuffer, sizeof(DivisionVertex)* verts);
		vertexBuffer_->Unlock();
		direct3DDevice_->SetStreamSource(0, vertexBuffer_, 0, sizeof(DivisionVertex));
		vertexBuffer_->Release();
	}



	void D3D9Renderer::setIndexBuffer(void* indexBuffer, int indexes)
	{
		// Create the index buffer.
		if (FAILED(direct3DDevice_->CreateIndexBuffer(indexes * sizeof(DWORD),
			D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
			D3DFMT_INDEX32,
			D3DPOOL_DEFAULT, &indexBuffer_, NULL)))
		{
			;
		}

		// Fill the index buffer.
		VOID* pData;
		if (FAILED(indexBuffer_->Lock(0, sizeof(DWORD)* indexes, (void**)&pData, 0)))
			;
		memcpy(pData, indexBuffer, sizeof(DWORD)* indexes);
		indexBuffer_->Unlock();
		direct3DDevice_->SetIndices(indexBuffer_);
		indexBuffer_->Release();
	}



	void D3D9Renderer::increaseReferenceCount()
	{
		referenceCount_++;
	}

	void D3D9Renderer::decreaseReferenceCount()
	{
		referenceCount_--;
	}

	short D3D9Renderer::getReferenceCount()
	{
		return referenceCount_;
	}

	void D3D9Renderer::clear()
	{
		direct3DDevice_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0xff, 0xff), 1.0f, 0);
	}



	void D3D9Renderer::beginScene()
	{
		direct3DDevice_->BeginScene();
	}



	void D3D9Renderer::endScene()
	{
		direct3DDevice_->EndScene();
	}



	void D3D9Renderer::present(void* window)
	{
		HWND win = static_cast<HWND>(window);
		direct3DDevice_->Present(NULL, NULL, win, NULL);
	}



	void D3D9Renderer::setTexture(void* resource)
	{
		D3D9Texture* texture = static_cast<D3D9Texture*>(resource);
		direct3DDevice_->SetTexture(0, texture->getTextureData());
		direct3DDevice_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		direct3DDevice_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	}



	void D3D9Renderer::setHandle(void* handle)
	{
		windowHandle_ = static_cast<HWND>(handle);
	}
}