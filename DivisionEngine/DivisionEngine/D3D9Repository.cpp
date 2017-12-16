#include "D3D9Repository.h"
#include "LoggerPool.h"

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
				->logError("Failed to create Direct3D device, " + result);
			return;
		}
	}



	D3D9Repository::~D3D9Repository()
	{
	}



	ResourceLoader* D3D9Repository::getTextureLoader()
	{
		return new D3D9TextureLoader(direct3DDevice_); // TODO: create members of these
	}



	ResourceLoader* D3D9Repository::getMeshLoader()
	{
		return new D3D9MeshLoader(direct3DDevice_); // TODO: create members of these
	}



	Entity* D3D9Repository::parseHeightmap(std::string filename, ResourceManager* rm) {
		Logger* logger = LoggerPool::getInstance()->getLogger("heightmap");
		logger->logInfo("Loading heightmap");
		FILE *f;
		errno_t err = fopen_s(&f, filename.c_str(), "rb");
		if (err != 0) return nullptr;
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f);
		const int fileSize = *(int*)&info[0x2];
		const int dataOffset = *(int*)(&info[0x0A]);
		const int width = *(int*)&info[0x12];
		const int height = *(int*)&info[0x16];
		const int bitCount = *(int*)&info[0x1C];
		const int dataSizeHeader = fileSize - dataOffset;

		int pad = 0;

		if ((width * (bitCount / 8)) % 4 != 0)
			pad = 4 - ((width * (bitCount / 8)) % 4);

		long size = width * (bitCount / 8) + pad;

		const int dataSizeCalculated = size*height;

		if (dataSizeCalculated != dataSizeHeader) {
			logger->logInfo("Expected data size not equal to calculated data size");
		}

		unsigned char* data = new unsigned char[dataSizeCalculated];
		if (dataOffset > 0)
			fseek(f, (long int)(dataOffset)-54, SEEK_CUR);

		DivisionVertex* vertices = new DivisionVertex[width * height];

		int index = 0, currentColumn, currentRow;

		fread(data, 1, dataSizeCalculated, f);
		for (int i = 0; i < width*height; i++) {
			currentColumn = floor(i / height);
			currentRow = i % height;


			int heightmapIndex;// = currentColumn + currentRow * size;
			heightmapIndex = (height - (currentRow+1)) * size + currentColumn;

			int y = data[heightmapIndex * (bitCount / 8)];
			DWORD grayValB = y;
			DWORD grayValG = y << 8;
			DWORD grayValR = y << 16;
			int grayColor = grayValR + grayValG + grayValB;
			int z = width / -2 + currentColumn;
			int x = height / -2 + currentRow;
			vertices[i] = { static_cast<float>(x),y / 10.0f - 52.5f, static_cast<float>(z), 0xff000000 + grayColor };
		}



		fclose(f);

		delete[] data;

		logger->logInfo("Successfully finished loading heightmap");

		return new Terrain(rm, vertices, width, height);
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
		return new WindowsInputManager();
	}
	


	void* D3D9Repository::getFrameworkInterface()
	{
		return direct3D_;
	}
}