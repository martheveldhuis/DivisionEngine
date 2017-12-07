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

		int i;
		FILE *f;
		errno_t err = fopen_s(&f, "nick.bmp", "rb");
		if (err != 0) return nullptr;
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f);
		int dataOffset = *(int*)(&info[0x0A]);

		const int length = *(int*)&info[0x12];
		const int width = *(int*)&info[0x16];
		const int g = *(int*)&info[0x1C];

		int pad = 0;

		if ((width * 3) % 4 != 0)
			pad = 4 - ((width * 3) % 4); 

		long size = width * 3+ pad;
		
		unsigned char* data = new unsigned char[size*length];
		if (dataOffset > 0)
			fseek(f, (long int)(dataOffset) -54, SEEK_CUR);
		DivisionVertex* vertices = new DivisionVertex[width * length];

		int index = 0;

		fread(data, sizeof(unsigned char), size * length, f);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				index = i * width + j;

				int heightmapIndex = j* width + i;
				int y = data[heightmapIndex];

				DWORD grayValB = int(y);
				DWORD grayValG = (int(y)) << 8;
				DWORD grayValR = (int(y)) << 16;
				int grayColor = grayValR + grayValG + grayValB;
				int x = i - width / 2 + 1;
				int z = j - length / 2 + 1;
				vertices[index] = { static_cast<float>(x), y / 20.0f - 23.5f, static_cast<float>(z), 0xff000000 + grayColor };
			}
		}


		fclose(f);

		delete[] data;


		return new Terrain(rm, vertices, width, length);
	}
	


	Renderer* D3D9Repository::getRenderer()
	{
		return new D3D9Renderer();
	}


	D3D9Repository::~D3D9Repository()
	{
	}
}