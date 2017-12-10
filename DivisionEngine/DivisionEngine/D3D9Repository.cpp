#include "D3D9Repository.h"


namespace Division
{
	LPDIRECT3D9 direct3D_ = NULL;
	D3D9Repository::D3D9Repository()
	{
	}

	ResourceLoader* D3D9Repository::getTextureLoader()
	{
		return nullptr;
	}

	ResourceLoader* D3D9Repository::getMeshLoader()
	{
		return nullptr;
	}

	Entity* D3D9Repository::parseHeightmap(std::string filename, ResourceManager* rm) {
		Logger* logger = LoggerPool::getInstance()->getLogger("heightmap");
		logger->logInfo("Loading heightmap");
		int i;
		FILE *f;
		errno_t err = fopen_s(&f, "heightmap2.bmp", "rb");
		if (err != 0) {
			logger->logInfo("An error occured reading the heightmap");
			return nullptr;
		}
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
			heightmapIndex = (height - currentRow) * size + currentColumn;

			int y = data[heightmapIndex * (bitCount / 8)];
			DWORD grayValB = y;
			DWORD grayValG = y << 8;
			DWORD grayValR = y << 16;
			int grayColor = grayValR + grayValG + grayValB;
			int z = width / -2 + currentColumn;
			int x = height / -2 + currentRow;
			vertices[i] = { static_cast<float>(x),y /2.0f - 82.5f, static_cast<float>(z), 0xff000000 + grayColor };
		}



		fclose(f);

		delete[] data;

		logger->logInfo("Successfully finished loading heightmap");

		return new Terrain(rm, vertices, width, height);

	
	}
	


	Renderer* D3D9Repository::getRenderer()
	{
		return new D3D9Renderer();
	}


	D3D9Repository::~D3D9Repository()
	{
	}
}