#ifndef DIVISION_RENDERER_H
#define DIVISION_RENDERER_H

#include <Windows.h>
#include "Resource.h"

namespace Division
{
	struct CUSTOMVERTEX
	{
		float x, y, z;      // 3D vertex position
		DWORD color;        // The vertex color
	};

	/// <summary>Abstract Renderer containing all functions every renderer should have.</summary>
	class Renderer {
	public:
		virtual ~Renderer() = 0 {};
		virtual void setup() = 0;
		/// <summary>Releases all previously initialized objects</summary>
		virtual void cleanup() = 0;
		/// <summary>Sets up the world, view, and projection transforms for pipeline.</summary>
		virtual void setupMatrices() = 0;
		virtual void setVertexBuffer(CUSTOMVERTEX* vertexBuffer, int) = 0;
		virtual void setIndexBuffer(void* indexBuffer, int indexes) = 0;
		virtual void setHandle(void*) = 0;
		virtual void setTexture(void*) = 0;
		virtual void* getDevice() = 0;
	};
}
#endif
