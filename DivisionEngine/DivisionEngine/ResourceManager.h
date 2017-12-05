#ifndef DIVISION_RESOURCEMANAGER_H
#define DIVISION_RESOURCEMANAGER_H

#include "Resource.h"
#include "TextureLoader.h"
#include "MeshLoader.h"

#include <map>
#include <d3dx9.h>

namespace Division
{
	class ResourceManager
	{
	public:
		ResourceManager(LPDIRECT3DDEVICE9);
		~ResourceManager();
		void addNewTexture(std::string);
		void addNewMesh(std::string);
		Resource* getTexture(std::string);
		Resource* getMesh(std::string);
		void removeTexture(std::string);
		void removeMesh(std::string);
	private:
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Resource*> meshes_;
		LPDIRECT3DDEVICE9 direct3Ddevice_;
	};
}
#endif
