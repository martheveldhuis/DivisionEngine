#include "D3D9MeshLoader.h"

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
		LPD3DXMESH mesh = NULL;
		LPD3DXBUFFER buffer = NULL; // Buffer with information about the texture file name and material properties.
		DWORD numberOfMaterials = 0L; // How many materials the loaded mesh has. Initialized to 0.
		std::vector<std::string> textureFileNames;

		HRESULT result = D3DXLoadMeshFromX(meshFile.c_str(), D3DXMESH_SYSTEMMEM,
			direct3DDevice_, NULL,
			&buffer, NULL, &numberOfMaterials,
			&mesh);
		if (FAILED(result))
		{
			std::string prefixedtMeshFile = "..\\" + meshFile;

			HRESULT result = D3DXLoadMeshFromX(prefixedtMeshFile.c_str(), D3DXMESH_SYSTEMMEM,
				direct3DDevice_, NULL,
				&buffer, NULL, &numberOfMaterials,
				&mesh);
			if (FAILED(result)) {
				LoggerPool::getInstance()->getLogger("MeshLoader")
					->logInfo("Failed to load mesh from file");
			}
		}

		D3DXMATERIAL* materials = (D3DXMATERIAL*)buffer->GetBufferPointer(); // Get pointer to data in the buffer

		D3DMATERIAL9* meshMaterials = new D3DMATERIAL9[numberOfMaterials];
		if (meshMaterials == NULL) {
			LoggerPool::getInstance()->getLogger("MeshLoader")
				->logInfo("Failed to get materials");
		}

		for (DWORD i = 0; i < numberOfMaterials; i++) {
			// Set the material.
			meshMaterials[i] = materials[i].MatD3D;

			// Set the ambient color for the material
			meshMaterials[i].Ambient = meshMaterials[i].Diffuse;

			// Check if the material has a texture, if so add to vector.
			if (materials[i].pTextureFilename != NULL &&
				lstrlenA(materials[i].pTextureFilename) > 0)
			{
				textureFileNames.push_back(materials[i].pTextureFilename);
			}
			else {
				textureFileNames.push_back("");
			}
		}

		buffer->Release();

		return new D3D9Mesh(mesh, meshMaterials, numberOfMaterials, textureFileNames);
	}


}