#include "D3D9Repository.h"
#include "LoggerPool.h"
#include "FileLoader.h"
#include "D3D9Mesh.h"
#include "SkyBox.h"

namespace Division
{
	D3D9Repository::D3D9Repository()
	{
		if (NULL == (direct3D_ = Direct3DCreate9(D3D_SDK_VERSION))) {
			LoggerPool::getInstance()->getLogger("D3DRepository")
				->logError("Failed to create Direct3D object");
			return;
		}

		D3DPRESENT_PARAMETERS direct3DParams;
		ZeroMemory(&direct3DParams, sizeof(direct3DParams));
		direct3DParams.Windowed = TRUE;
		direct3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		direct3DParams.BackBufferFormat = D3DFMT_UNKNOWN;
		direct3DParams.EnableAutoDepthStencil = true;
		direct3DParams.AutoDepthStencilFormat = D3DFMT_D16;

		HWND windowHandle = CreateWindowA("STATIC", "dummy", NULL, 100, 100, 800, 600,
			NULL, NULL, NULL, NULL);

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
		
		bool useTexture = texturefile != "";

		int index = 0, currentColumn, currentRow, heightmapIndex;

		FileData heightmapData, textureFileData;

		textureFileData = FileLoader::parseBmp(texturefile);
		heightmapData = FileLoader::parseBmp(filename);
		
		DivisionVertex* vertices = new DivisionVertex[heightmapData.width *
													  heightmapData.height];

		unsigned char* heightData = heightmapData.rawData;
		unsigned int* textureColorData = textureFileData.colorData;

		for (int i = 0; i < heightmapData.width * heightmapData.height; i++) {
			currentColumn = floor(i / heightmapData.height);
			currentRow = i % heightmapData.height;

			// convert vertices index to the corresponding heightmap pixel
			heightmapIndex = (heightmapData.height - (currentRow + 1)) *
							  heightmapData.rowByteCount + currentColumn * heightmapData.byteCount;

			int y = heightData[heightmapIndex];
			unsigned int vertexColor = 0xff000000;

			if (useTexture) {
				int colorIndex = (textureFileData.height - currentRow) + currentColumn *
								  textureFileData.rowByteCount;

				colorIndex *= textureFileData.byteCount;
				// Get colors from texture

				vertexColor += textureColorData[i];
			}

			int z = heightmapData.width / -2 + currentColumn;
			int x = heightmapData.height / -2 + currentRow;

			float textureX = currentColumn / (heightmapData.width - 1.0f);
			float textureY = currentRow / (heightmapData.height - 1.0f);
			vertices[i] = { static_cast<float>(x ),y / 30.0f - 6.5f, static_cast<float>(z ),
				textureX , textureY };
		}

		return new Terrain(rm, vertices, heightmapData.width, heightmapData.height);
	}
	


	Entity* D3D9Repository::getSkyBox(ResourceManager* rm)
	{
		float side = 1.0f;
		float texture = 0.125f;
		int i = 0;

		DivisionVertex* vertices = new DivisionVertex[8];
		
		vertices[0] = { -side, side, -side, 0,0 };    // vertex 0
		vertices[1] = { side, side, -side, 1,0};     // vertex 1
		vertices[2] = { -side, -side, -side,1,1};   // 2
		vertices[3] = { side, -side, -side, 0,1};  // 3
		vertices[4] = { -side, side, side, 1,0};     // ...
		vertices[5] = { side, side, side, 0,0 };
		vertices[6] = { -side, -side, side, 0,1};
		vertices[7] = { side, -side, side, 1,1};
		

		return new SkyBox(rm, vertices);

	}


	Renderer* D3D9Repository::getRenderer()
	{
		return new D3D9Renderer(direct3DDevice_);
	}



	Window* D3D9Repository::getWindow(std::string title)
	{
		return new Win32Window(title);
	}

	InputManager * D3D9Repository::getInputManager()
	{
		return new DirectInputManager();
	}
	


	void* D3D9Repository::getFrameworkInterface()
	{
		return direct3D_;
	}
}