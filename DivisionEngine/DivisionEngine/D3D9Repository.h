#ifndef DIVISION_D3D9REPOSITORY_H
#define DIVISION_D3D9REPOSITORY_H

#include <string>

#include "ResourceLoader.h"
#include "Renderer.h"
#include "D3D9TextureLoader.h"
#include "D3D9MeshLoader.h"
#include "D3D9Renderer.h"

namespace Division
{
	class D3D9Repository
	{
	public:
		D3D9Repository();
		~D3D9Repository();
		ResourceLoader* getTextureLoader();
		ResourceLoader* getMeshLoader();
		Renderer* getRenderer();
	};
}

#endif // ! D3D9DIVISION_REPOSITORY_H