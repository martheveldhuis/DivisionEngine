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

		// Open the bmp safely (don't allow edits while opened).
		// Open in read & byte mode to extract pixel data. (3rd param).
		openError = fopen_s(&fileHandle, fileName.c_str(), "rb");

		// Return invalid file info with invalid bool set to false.
		if (openError != 0) {
			fileData.valid = false;
			logger->logInfo("Error loading file");
			return fileData;
		}

		// Read the bmp infoheader of 54 bytes.
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, fileHandle);

		// Retrieve file info from the header.
		const int fileSize = *(int*)&info[0x2];
		const int dataOffset = *(int*)(&info[0x0A]);
		const int width = *(int*)&info[0x12];
		const int height = *(int*)&info[0x16];
		const int bitCount = *(int*)&info[0x1C];

		// Determine the data-size in bytes according to the header.
		const int dataSizeHeader = fileSize - dataOffset;

		// Calculate padding in bytes using the bitcount of the file.
		// Every row must be a multiple of 4 bytes.
		// The row size without padding is calculated by multiplying the amount
		// of bytes per pixel by the width.
		// After that, a modulo 4 can be used to check how many bytes of
		// padding are needed.
		int pad = 0;
		int byteCount = bitCount / 8;
		if ((width * byteCount) % 4 != 0)
			pad = 4 - ((width * byteCount) % 4);

		// Row size including padding in bytes.
		long rowSize = width * byteCount + pad;

		// Determine the data-size in bytes according to the byte info.
		const int dataSizeCalculated = rowSize*height;

		// Compare data-size according to header with self-calculated size.
		if (dataSizeCalculated != dataSizeHeader) {
			fileData.valid = false;
			logger->logInfo("Expected data size not equal to calculated data size");
			return fileData;
		}

		unsigned char* data = new unsigned char[dataSizeCalculated];
		unsigned int* colorData = new unsigned int[width * height];

		// Seek to the start position of the color data.
		if (dataOffset > 0)
			fseek(fileHandle, (long int)(dataOffset)-54, SEEK_CUR);

		// Read the data with the size of the color data in bits.
		fread(data, 1, dataSizeCalculated, fileHandle);
		
		int bmpIndex, currentColumn, currentRow;
		
		// Loop through each pixel and assign the values to the colorData array.
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

		// Close the handle after use.
		fclose(fileHandle);

		// Set file data on the struct.
		fileData.byteCount = byteCount;
		fileData.rawData = data;
		fileData.width = width;
		fileData.height = height;
		fileData.rowByteCount = rowSize;
		fileData.colorData = colorData;

		return fileData;
	}
}