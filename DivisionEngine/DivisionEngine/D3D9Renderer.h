#ifndef DIVISION_D3D9RENDERER_H
#define DIVISION_D3D9RENDERER_H

#include "Renderer.h"
#include <d3d9.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning
#include <strsafe.h>
#pragma warning( default : 4996 )

namespace Division
{

	class D3D9Renderer : public Renderer
	{
	public:
		D3D9Renderer(LPDIRECT3D9 direct3D, LPDIRECT3DDEVICE9 direct3Ddevice, HWND windowHandle);
		~D3D9Renderer();
		void setup();
		void initializeGraphics();
		/// <summary>Releases all previously initialized objects</summary>
		void cleanup();
		/// <summary>Sets up the world, view, and projection transforms for pipeline.</summary>
		void setupMatrices();
		void setVertexBuffer(struct CUSTOMVERTEX *vertices, int verts);
		void setIndexBuffer(void *vertices, int indexes);
		void* getDevice() { return direct3Ddevice_; }
		virtual void setTexture(void*);
	private:
		LPDIRECT3D9             direct3D_ = NULL; // To create 3D device, needs release
		LPDIRECT3DDEVICE9       direct3Ddevice_ = NULL; // Device to render with
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // Buffer to hold vertices
		LPDIRECT3DINDEXBUFFER9  indexBuffer_ = NULL; // Buffer to hold indices
		HWND windowHandle_;
	};
}

#endif // !DIVISION_D3D9RENDERER_H