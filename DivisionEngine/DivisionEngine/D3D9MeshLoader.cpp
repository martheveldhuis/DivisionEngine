#include "D3D9MeshLoader.h"
#include "LoggerPool.h"
#include "D3D9Mesh.h"
#include "SkyBox.h"

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
		LPD3DXMESH mesh = NULL;
		LPD3DXBUFFER buffer = NULL;
		DWORD numberOfMaterials = 0L;
		std::vector<std::string> textureFileNames;

		HRESULT result = D3DXLoadMeshFromX(meshFile.c_str(), 
										   D3DXMESH_SYSTEMMEM,
										   direct3DDevice_, NULL, &buffer,
										   NULL, &numberOfMaterials, &mesh);
		if (FAILED(result))
		{
			std::string prefixedtMeshFile = "..\\" + meshFile;

			HRESULT result = D3DXLoadMeshFromX(prefixedtMeshFile.c_str(), 
											   D3DXMESH_SYSTEMMEM,
											   direct3DDevice_, NULL, &buffer,
											   NULL, &numberOfMaterials,
											   &mesh);
			if (FAILED(result)) {
				LoggerPool::getInstance()->getLogger("MeshLoader")->
					logInfo("Failed to load mesh from file: " + result);
			}
		}

		D3DXMATERIAL* materials = (D3DXMATERIAL*)buffer->GetBufferPointer();
		D3DMATERIAL9* meshMaterials = new D3DMATERIAL9[numberOfMaterials];

		if (meshMaterials == NULL) {
			LoggerPool::getInstance()->getLogger("MeshLoader")->
				logInfo("Failed to get materials");
		}

		for (DWORD i = 0; i < numberOfMaterials; i++) {
			meshMaterials[i] =			materials[i].MatD3D;
			meshMaterials[i].Ambient =	meshMaterials[i].Diffuse;

			LPCSTR textureFileName =	materials[i].pTextureFilename;

			if (textureFileName != NULL && lstrlenA(textureFileName) > 0) {
				textureFileNames.push_back(textureFileName);
			}
			else {
				textureFileNames.push_back("");
			}
		}

		buffer->Release();

		return new D3D9Mesh(mesh, meshMaterials, numberOfMaterials, 
							textureFileNames);
	}

	Mesh* D3D9MeshLoader::getSkyBox()
	{

		LPD3DXMESH d3Mesh = NULL;
		LPD3DXBUFFER buffer = NULL;
		D3DXCreateBox(direct3DDevice_, 3, 3, 3, &d3Mesh, NULL);

		D3D9Mesh* m = new D3D9Mesh(d3Mesh, "banana.bmp");

		return m;
	}


}