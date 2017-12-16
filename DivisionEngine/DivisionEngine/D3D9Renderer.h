#ifndef DIVISION_D3D9RENDERER_H
#define DIVISION_D3D9RENDERER_H

#include "Renderer.h"
#include <Windows.h>
#include <d3d9.h>

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
		void* getDevice() { return direct3DDevice_; }
		void setWorldMatrix(Position*);
		void setTexture(void*);
		void setHandle(void*);
	private:
		LPDIRECT3DDEVICE9 direct3DDevice_; // Device to render with
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // Buffer to hold vertices
		LPDIRECT3DINDEXBUFFER9  indexBuffer_ = NULL; // Buffer to hold indices
		HWND windowHandle_;
	};
}

#endif // !DIVISION_D3D9RENDERER_H