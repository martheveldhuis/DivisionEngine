#include "D3D9Repository.h"
#include "LoggerPool.h"
#include "FileLoader.h"
#include "D3D9Mesh.h"
#include "D3D9Camera.h"
#include "D3D9SkyBox.h"
#include "D3D9Terrain.h"

namespace Division
{
	D3D9Repository::D3D9Repository()
	{
		if (NULL == (direct3D_ = Direct3DCreate9(D3D_SDK_VERSION))) {
			LoggerPool::getInstance()->getLogger("D3DRepository")
				->logError("Failed to create Direct3D object");
			return;
		}

		// Set up the dx parameters.
		D3DPRESENT_PARAMETERS direct3DParams;
		ZeroMemory(&direct3DParams, sizeof(direct3DParams));
		direct3DParams.Windowed = TRUE;
		direct3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		direct3DParams.BackBufferFormat = D3DFMT_UNKNOWN;
		direct3DParams.EnableAutoDepthStencil = true;
		direct3DParams.AutoDepthStencilFormat = D3DFMT_D16;

		// Create a dummy window to create a direct3D device without a visible window present.
		HWND windowHandle = CreateWindowA("STATIC", "dummy", NULL, 100, 100, 800, 600,
			NULL, NULL, NULL, NULL);

		// Attempt to create the direct3D device, log on fail.
		HRESULT result = direct3D_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &direct3DParams, &direct3DDevice_);

		if (FAILED(result)) {
			LoggerPool::getInstance()->getLogger("D3DRepository")
				->logError("Failed to create Direct3D device");
			return;
		}
	}



	D3D9Repository::~D3D9Repository()
	{
		if (textureLoader_)
			delete textureLoader_;
		if (meshLoader_)
			delete meshLoader_;
	}



	ResourceLoader* D3D9Repository::getTextureLoader()
	{
		if (!textureLoader_)
			textureLoader_ = new D3D9TextureLoader(direct3DDevice_);
			
		return textureLoader_;
	}



	ResourceLoader* D3D9Repository::getMeshLoader()
	{
		if (!meshLoader_)
			meshLoader_ = new D3D9MeshLoader(direct3DDevice_);
		
		return meshLoader_;
	}



	Entity* D3D9Repository::getTerrain(std::string filename, ResourceManager* rm, std::string texturefile = "") {
		
		int currentColumn, currentRow, heightmapIndex;

		FileData heightmapData, textureFileData;

		// Use the file loader to parse the texture and heightmap bmp.
		textureFileData = FileLoader::parseBmp(texturefile);
		heightmapData = FileLoader::parseBmp(filename);
		
		// Create the vertex array.
		DivisionVertex* vertices = new DivisionVertex[heightmapData.width *
													  heightmapData.height];

		unsigned char* heightData = heightmapData.rawData;

		// Single for loop to create all vertices of the terrain.
		for (int i = 0; i < heightmapData.width * heightmapData.height; i++) {
			currentColumn = floor(i / heightmapData.height);
			currentRow = i % heightmapData.height;

			// Convert vertices index to the corresponding heightmap pixel.
			heightmapIndex = (heightmapData.height - (currentRow + 1)) *
							  heightmapData.rowByteCount + currentColumn * heightmapData.byteCount;

			// Get the elevation from the heightmap pixel color.
			int y = heightData[heightmapIndex];

			int z = heightmapData.width / -2 + currentColumn;
			int x = heightmapData.height / -2 + currentRow;

			// Calculate the texture positions.
			float textureX = currentColumn / (heightmapData.width - 1.0f);
			float textureY = currentRow / (heightmapData.height - 1.0f);

			// Create a new vertex with the x, y and z position, and texture uv mapping.
			vertices[i] = { x / 8.0f, y / 30.0f - 26.5f, z / 8.0f,
				textureX , textureY };
		}

		return new D3D9Terrain(rm, vertices, heightmapData.width, heightmapData.height);
	}
	


	Entity* D3D9Repository::getSkyBox(ResourceManager* rm)
	{

		return new D3D9SkyBox(rm, 1);

	}


	Renderer* D3D9Repository::getRenderer()
	{
		return new D3D9Renderer(direct3DDevice_);
	}



	Window* D3D9Repository::getWindow(std::string title)
	{
		return new Win32Window(title);
	}



	Entity* D3D9Repository::getCamera(ResourceManager* resourceManager, 
									  float x, float y, float z, float xAngle,
									  float yAngle, float zAngle)
	{
		return new D3D9Camera(resourceManager, x, y, z, xAngle, yAngle, zAngle);
	}



	InputManager* D3D9Repository::getInputManager()
	{
		return new DirectInputManager();
	}
	


	void* D3D9Repository::getFrameworkInterface()
	{
		return direct3D_;
	}
}