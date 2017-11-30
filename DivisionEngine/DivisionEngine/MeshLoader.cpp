#include "MeshLoader.h"
#include "Win32Window.h"
#include "D3D9Renderer.h"

namespace Division
{
	MeshLoader::MeshLoader()
	{
	}



	MeshLoader::~MeshLoader()
	{
	}



	LPD3DXMESH MeshLoader::getMesh(std::string meshFile)
	{
		// TODO: change this to return a mesh object (resource)
		// TODO: put d3d object and d3d device somewhere so it can be shared everywhere
		Win32Window* a = new Win32Window();

		HWND hWnd = a->getWindowHandle();

		D3D9Renderer* rend = new D3D9Renderer(NULL, NULL, hWnd);
		rend->setup();
		LPDIRECT3DDEVICE9 g_pd3dDevice = rend->direct3Ddevice_;


		///////////////////////////////////////////////////////////////

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
				// Log that this failed
			}
		}

		return mesh;
	}
}