#include "MeshLoader.h"

#include <vector>

namespace Division
{
	MeshLoader::MeshLoader()
	{
	}



	MeshLoader::~MeshLoader()
	{
	}



	Mesh* MeshLoader::getResource(std::string meshFile, void* d3dDevice)
	{
		// TODO: move this line somewhere else?
		LPDIRECT3DDEVICE9 g_pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(d3dDevice);

		LPD3DXMESH mesh = NULL;
		LPD3DXBUFFER buffer = NULL; // Buffer with information about the texture file name and material properties.
		DWORD numberOfMaterials = 0L; // How many materials the loaded mesh has. Initialized to 0.
		std::vector<std::string> textureFileNames;

		if (FAILED(D3DXLoadMeshFromX(meshFile.c_str(), D3DXMESH_SYSTEMMEM,
			g_pd3dDevice, NULL,
			&buffer, NULL, &numberOfMaterials,
			&mesh)))
		{
			std::string prefixedtMeshFile = "..\\" + meshFile;

			HRESULT result = D3DXLoadMeshFromX(prefixedtMeshFile.c_str(), D3DXMESH_SYSTEMMEM,
				g_pd3dDevice, NULL,
				&buffer, NULL, &numberOfMaterials,
				&mesh);
			if (FAILED(result)) {
				// TODO: Log that this failed.
			}
		}

		D3DXMATERIAL* materials = (D3DXMATERIAL*)buffer->GetBufferPointer(); // Get pointer to data in the buffer

		D3DMATERIAL9* meshMaterials = new D3DMATERIAL9[numberOfMaterials];
		if (meshMaterials == NULL) {
			// TODO: Log that this failed.
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