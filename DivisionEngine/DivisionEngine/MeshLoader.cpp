#include "MeshLoader.h"
#include "Win32Window.h"
#include "D3D9Renderer.h"
#include "Mesh.h"

namespace Division
{
	MeshLoader::MeshLoader()
	{
	}



	MeshLoader::~MeshLoader()
	{
	}

	Resource* MeshLoader::getResource(std::string meshFile, void* d3dDevice)
	{
		// TODO: move this line somewhere else?
		LPDIRECT3DDEVICE9 g_pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(d3dDevice);

		LPD3DXBUFFER pD3DXMtrlBuffer;
		DWORD g_dwNumMaterials = 0L;
		LPD3DXMESH mesh = NULL;


		if (FAILED(D3DXLoadMeshFromX(meshFile.c_str(), D3DXMESH_SYSTEMMEM,
			g_pd3dDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
			&mesh)))
		{
			std::string prefixedtMeshFile = "..\\" + meshFile;

			HRESULT result = D3DXLoadMeshFromX(prefixedtMeshFile.c_str(), D3DXMESH_SYSTEMMEM,
				g_pd3dDevice, NULL,
				&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
				&mesh);
			if (FAILED(result))
			{
				// TODO: Log that this failed.
			}
		}

		// TODO: add proper implementation
		return new Mesh(mesh);
	}


}