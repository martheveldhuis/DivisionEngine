#ifndef DIVISION_D3D9RENDERER_H
#define DIVISION_D3D9RENDERER_H

#include "Renderer.h"
#include <Windows.h>
#include <d3d9.h>

#include "D3D9Texture.h"
#include "D3D9Mesh.h"

namespace Division
{

	class D3D9Renderer : public Renderer
	{
	public:
		D3D9Renderer();
		~D3D9Renderer();
		void setup();
		void initializeGraphics();
		/// <summary>Releases all previously initialized objects</summary>
		void cleanup();
		/// <summary>Sets up the world, view, and projection transforms for pipeline.</summary>
		void setupMatrices();
		void setVertexBuffer(struct DivisionVertex *vertices, int verts);
		void setIndexBuffer(void *vertices, int indexes);
		void* getDevice() { return direct3Ddevice_; }
		void setTexture(void*);
		void setHandle(void*);
	private:
		static LPDIRECT3D9      direct3D_; // To create 3D device, needs release
		static LPDIRECT3DDEVICE9 direct3Ddevice_; // Device to render with
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // Buffer to hold vertices
		LPDIRECT3DINDEXBUFFER9  indexBuffer_ = NULL; // Buffer to hold indices
		HWND windowHandle_;
	};
}

#endif // !DIVISION_D3D9RENDERER_H