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
		/**
			Releases all previously initialized objects.
		*/
		~D3D9Renderer();
		void setup();
		/**
			Set render graphic specific options.
		*/
		void initializeGraphics();
		/**
			Sets up the view, and projection transforms in the pipeline.
		*/
		void setupMatrices();
		/**
			Allocates space for the vertexBuffer in the graphics device, then copies the
			buffer to the device.
			@param DivisionVertex Array of vertices to be renderered in the next draw.
			@param int Amount of vertices to be drawn.
		*/
		void setVertexBuffer(struct DivisionVertex* vertices, int verts);
		/**
			Allocates space for the indexBuffer in the graphics device, then copies the
			buffer to the device.
			@param void* Array of indices to be renderered in the next draw.
			@param int Amount of indices to be drawn.
		*/
		void setIndexBuffer(void* vertices, int indexes);
		void* getDevice() { return direct3DDevice_; }

		void clear();
		void beginScene();
		void endScene();
		void present(void*);

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