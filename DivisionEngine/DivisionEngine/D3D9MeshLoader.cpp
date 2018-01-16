#include "D3D9MeshLoader.h"
#include "D3D9Mesh.h"
#include "LoggerPool.h"

#include <d3dx9.h>

namespace Division
{
	D3D9MeshLoader::D3D9MeshLoader(LPDIRECT3DDEVICE9 direct3DDevice)
		: direct3DDevice_(direct3DDevice)
	{
	}



	D3D9MeshLoader::~D3D9MeshLoader()
	{
	}



	Mesh* D3D9MeshLoader::getResource(std::string meshFile)
	{
		LPD3DXMESH mesh = NULL;		// Mesh object.
		LPD3DXBUFFER buffer = NULL;	// Buffer for holding material properties.
		DWORD numberOfMaterials = 0L;
		std::vector<std::string> textureFileNames;

		HRESULT result = D3DXLoadMeshFromX(meshFile.c_str(), 
										   D3DXMESH_SYSTEMMEM,
										   direct3DDevice_, NULL, &buffer,
										   NULL, &numberOfMaterials, &mesh);
		if (FAILED(result))
		{
			std::string prefixedMeshFile = "..\\" + meshFile;

			HRESULT result = D3DXLoadMeshFromX(prefixedMeshFile.c_str(),
											   D3DXMESH_SYSTEMMEM,
											   direct3DDevice_, NULL, &buffer,
											   NULL, &numberOfMaterials,
											   &mesh);
			if (FAILED(result)) {
				LoggerPool::getInstance()->getLogger("MeshLoader")->
					logInfo("Failed to load mesh from file");
			}
		}
		LoggerPool::getInstance()->getLogger("MeshLoader")->
			logInfo("Failed to load mesh from file");

		// Set up structures for extracting material information.
		D3DXMATERIAL* materials = (D3DXMATERIAL*)buffer->GetBufferPointer();
		D3DMATERIAL9* meshMaterials = new D3DMATERIAL9[numberOfMaterials];

		if (meshMaterials == NULL) {
			LoggerPool::getInstance()->getLogger("MeshLoader")->
				logInfo("Failed to get materials");
		}

		for (DWORD i = 0; i < numberOfMaterials; i++) {
			// Copy the material.
			meshMaterials[i] =			materials[i].MatD3D;
			// Set the lighting type for the material.
			meshMaterials[i].Ambient =	meshMaterials[i].Diffuse;

			LPCSTR textureFileName =	materials[i].pTextureFilename;

			// Set the texture file name if it is specified in the .x file.
			if (textureFileName != NULL && lstrlenA(textureFileName) > 0) {
				textureFileNames.push_back(textureFileName);
			}
		}

		buffer->Release();

		return new D3D9Mesh(mesh, meshMaterials, numberOfMaterials, 
							textureFileNames);
	}


}