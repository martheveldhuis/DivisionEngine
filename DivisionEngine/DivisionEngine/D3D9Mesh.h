#ifndef DIVISION_D3D9MESH_H
#define DIVISION_D3D9MESH_H

#include <d3dx9.h>

#include "Mesh.h"
#include "D3D9Texture.h"

namespace Division 
{
	/**
		Direct 3D mesh implementation of a mesh resource.
	*/
	class D3D9Mesh : public Mesh
	{
	public:
		/**
			Creates the Direct 3D mesh object using framework specific
			parameters.
			@param meshData The direct 3d mesh data defining the mesh.
			@param meshMaterials The direct 3d mesh materials.
			@param numberOfMaterials The number of materials for this mesh.
			@param textureFileNames The names of the default textures.
		*/
		D3D9Mesh(LPD3DXMESH meshData, D3DMATERIAL9* meshMaterials, 
				 DWORD numberOfMaterials, 
				 std::vector<std::string> textureFileNames);
		~D3D9Mesh();
		std::vector<std::string> getTextureFileNames();
		void setTextures(std::map<std::string, Resource*>);
		void draw(Renderer*, std::map<std::string, Resource*>);
	private:
		LPD3DXMESH meshData_ = NULL; 
		D3DMATERIAL9* meshMaterials_ = NULL;
		DWORD numberOfMaterials_ = 0L;
		std::vector<std::string> textureFileNames_;
		std::map<std::string, Resource*> textures_;
	};
}

#endif