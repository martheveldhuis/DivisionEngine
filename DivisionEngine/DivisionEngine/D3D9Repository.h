#ifndef DIVISION_D3D9REPOSITORY_H
#define DIVISION_D3D9REPOSITORY_H

#include <string>

#include "ResourceLoader.h"
#include "Repository.h"
#include "D3D9TextureLoader.h"
#include "D3D9MeshLoader.h"
#include "D3D9Renderer.h"
#include "D3D9Terrain.h"
#include "D3D9SkyBox.h"
#include "Win32Window.h"
#include "DirectInputManager.h"

namespace Division
{
	/**
		The repository for creating DirectX9 specific objects.
		This will create and hold the direct3D device and direct3D
		object for use within other D3D9 dependent classes.
	*/
	class D3D9Repository : public Repository
	{
	public:
		D3D9Repository();
		~D3D9Repository();
		void* getFrameworkInterface();
		ResourceLoader* getTextureLoader();
		ResourceLoader* getMeshLoader();
		Entity* getTerrain(std::string, ResourceManager*, std::string);
		Renderer* getRenderer();
		Window* getWindow(std::string);
		Entity* getCamera(ResourceManager* resourceManager,
						float x = 0, float y = 0, float z = 0,
						float xAngle = 0, float yAngle = 0, float zAngle = 0);
		InputManager* getInputManager();
		Entity* getSkyBox(ResourceManager*);
	private:
		LPDIRECT3D9 direct3D_ = NULL;
		LPDIRECT3DDEVICE9 direct3DDevice_ = NULL;
		D3D9TextureLoader* textureLoader_ = NULL;
		D3D9MeshLoader* meshLoader_ = NULL;
	};
}

#endif // ! D3D9DIVISION_REPOSITORY_H