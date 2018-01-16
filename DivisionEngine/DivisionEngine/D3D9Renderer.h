#ifndef DIVISION_D3D9RENDERER_H
#define DIVISION_D3D9RENDERER_H

#include "Renderer.h"
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace Division
{
	/**
		Renderer for DirectX9 to wrap render functionality.
	*/
	class D3D9Renderer : public Renderer
	{
	public:
		/**
			Create a new renderer with an existing DirectX device.
		*/
		D3D9Renderer(LPDIRECT3DDEVICE9);
		~D3D9Renderer();
		void setup();
		void initializeGraphics();
		void setupMatrices();
		void setVertexBuffer(struct DivisionVertex* vertices, int verts);
		void setIndexBuffer(void* vertices, int indexes);
		/**
			Gets the directx9 device.
			@returns Pointer to the direct3D device.
		*/
		void* getDevice() { return direct3DDevice_; }

		void increaseReferenceCount() { referenceCount_++; };
		void decreaseReferenceCount() { referenceCount_--; };
		short getReferenceCount() { return referenceCount_; };

		void clear();
		void beginScene();
		void endScene();
		void present(void*);

		void setWorldMatrix(Position*);
		void setTexture(void*);
		void setHandle(void*);

		virtual void setCameraMatrix(void*);
	private:
		LPDIRECT3DDEVICE9 direct3DDevice_;
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL;
		LPDIRECT3DINDEXBUFFER9  indexBuffer_ = NULL;
		HWND windowHandle_;
		D3DXMATRIX* cameraView_;
		short referenceCount_;
	};
}

#endif // !DIVISION_D3D9RENDERER_H