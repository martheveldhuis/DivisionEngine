#ifndef DIVISION_RESOURCEMANAGER_H
#define DIVISION_RESOURCEMANAGER_H

#include <map>
#include <d3dx9.h>

#include "D3D9TextureLoader.h"
#include "D3D9MeshLoader.h"
#include "D3D9Mesh.h"
#include "LoggerPool.h"

namespace Division
{
	class ResourceManager
	{
	public:
		ResourceManager(ResourceLoader*, ResourceLoader*);
		~ResourceManager();
		Resource* getTexture(std::string);
		Mesh* getMesh(std::string);
		void removeTexture(std::string);
		void removeMesh(std::string);
	private:
		Resource* addNewTexture(std::string);
		Resource* addNewMesh(std::string);
		ResourceLoader* textureLoader_;
		ResourceLoader* meshLoader_;
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Resource*> meshes_;
		LPDIRECT3DDEVICE9 direct3Ddevice_;
	};
}
#endif
