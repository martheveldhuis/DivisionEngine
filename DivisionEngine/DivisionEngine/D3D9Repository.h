#ifndef DIVISION_D3D9REPOSITORY_H
#define DIVISION_D3D9REPOSITORY_H

#include <string>

#include "ResourceLoader.h"
#include "Terrain.h"
#include "Repository.h"
#include "D3D9TextureLoader.h"
#include "D3D9MeshLoader.h"
#include "D3D9Renderer.h"
#include "Win32Window.h"

namespace Division
{
	class D3D9Repository : public Repository
	{
	public:
		D3D9Repository();
		~D3D9Repository();
		void* getFrameworkInterface();
		ResourceLoader* getTextureLoader();
		MeshLoader* getMeshLoader();
		Entity* getTerrain(std::string, ResourceManager*, std::string);
		Renderer* getRenderer();
		Window* getWindow(std::string);
	private:
		LPDIRECT3D9 direct3D_ = NULL;
		LPDIRECT3DDEVICE9 direct3DDevice_ = NULL;
		HWND windowHandle_ = NULL;
	};
}

#endif // ! D3D9DIVISION_REPOSITORY_H