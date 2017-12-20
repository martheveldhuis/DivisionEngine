#include "FileLoader.h"
#include "LoggerPool.h"

namespace Division
{
	FileLoader::~FileLoader()
	{
	}



	FileData Division::FileLoader::parseBmp(std::string fileName)
	{
		FileData fileData;
		fileData.valid = true;

		Logger* logger = LoggerPool::getInstance()->getLogger("terrain");
		logger->logInfo("Loading heightmap");

		FILE* fileHandle;
		errno_t openError;

		openError = fopen_s(&fileHandle, fileName.c_str(), "rb");

		if (openError != 0) {
			fileData.valid = false;
			logger->logInfo("Error loading file");
			return fileData;
		}

		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, fileHandle);
		const int fileSize = *(int*)&info[0x2];
		const int dataOffset = *(int*)(&info[0x0A]);
		const int width = *(int*)&info[0x12];
		const int height = *(int*)&info[0x16];
		const int bitCount = *(int*)&info[0x1C];
		const int dataSizeHeader = fileSize - dataOffset;

		int pad = 0;
		int byteCount = bitCount / 8;
		if ((width * byteCount) % 4 != 0)
			pad = 4 - ((width * byteCount) % 4);

		long rowSize = width * byteCount + pad;

		const int dataSizeCalculated = rowSize*height;

		if (dataSizeCalculated != dataSizeHeader) {
			fileData.valid = false;
			logger->logInfo("Expected data size not equal to calculated data size");
			return fileData;
		}

		unsigned char* data = new unsigned char[dataSizeCalculated];
		unsigned int* colorData = new unsigned int[width * height];

		if (dataOffset > 0)
			fseek(fileHandle, (long int)(dataOffset)-54, SEEK_CUR);

		fread(data, 1, dataSizeCalculated, fileHandle);
		
		int bmpIndex, currentColumn, currentRow;
		for (int i = 0; i < width * height; i++) {
			currentColumn = floor(i /height);
			currentRow = i % height;

			bmpIndex = ((height - (currentRow + 1)) *
				rowSize + currentColumn  * byteCount);
			if (byteCount == 3) {
				int rVal = data[bmpIndex - 1] << 16;
				int gVal = data[bmpIndex - 1 + 8] << 8;
				int bVal = data[bmpIndex - 1 + 16];
				unsigned int cVal = rVal + gVal + bVal;
				colorData[i] = cVal;
			}

		}


		fclose(fileHandle);

		fileData.byteCount = byteCount;
		fileData.rawData = data;
		fileData.width = width;
		fileData.height = height;
		fileData.rowByteCount = rowSize;
		fileData.colorData = colorData;

		return fileData;
	}
}