#ifndef DIVISION_D3D9MESH_H
#define DIVISION_D3D9MESH_H

#include <d3dx9.h>
#include <string>
#include <vector>
#include <map>

#include "Resource.h"
#include "D3D9Texture.h"
#include "Mesh.h"
#include "Renderer.h"

namespace Division 
{
	class D3D9Mesh : public Mesh
	{
	public:
		D3D9Mesh(LPD3DXMESH, D3DMATERIAL9*, DWORD, std::vector<std::string>);
		~D3D9Mesh();
		std::vector<std::string> getTextureFileNames();
		void setTextures(std::map<std::string, Resource*>);
		std::map<std::string, Resource*> getTextures();
		int getNumberOfMaterials();
		void draw(Renderer*);
	private:
		LPD3DXMESH meshData_ = NULL; 
		D3DMATERIAL9* meshMaterials_ = NULL;
		DWORD numberOfMaterials_ = 0L;
		std::vector<std::string> textureFileNames_; // For loading textures from .x file
		std::map<std::string, Resource*> textures_;
	};
}

#endif