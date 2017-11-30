#ifndef DIVISION_D3D9RENDERER_H
#define DIVISION_D3D9RENDERER_H

#include "Renderer.h"
#include <Windows.h>
#include <d3d9.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning
#include <strsafe.h>
#pragma warning( default : 4996 )

namespace Division {
	struct CUSTOMVERTEX
	{
		float x, y, z;      // 3D vertex position
		DWORD color;        // The vertex color
	};

	class D3D9Renderer : public Renderer
	{
	public:
		D3D9Renderer(LPDIRECT3D9 direct3D, LPDIRECT3DDEVICE9 direct3Ddevice, HWND windowHandle);
		~D3D9Renderer();
		void render(int);
		void render();
		void setup();
		void initGraphics();
		/// <summary>Releases all previously initialized objects</summary>
		void cleanup();
		/// <summary>Sets up the world, view, and projection transforms for pipeline.</summary>
		void setupMatrices();
		void setVertexBuffer(struct CUSTOMVERTEX *vertices, int verts);
		void setIndexBuffer(void *vertices, int indexes);
		LPDIRECT3DDEVICE9 getDevice() { return direct3Ddevice_; }
		LPDIRECT3DDEVICE9       direct3Ddevice_ = NULL; // Device to render with
	private:
		LPDIRECT3D9             direct3D_ = NULL; // To create 3D device, needs release
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // Buffer to hold vertices
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL; // Buffer to hold indices
		HWND windowHandle_;
	};
}

#endif // !DIVISION_D3D9RENDERER_H