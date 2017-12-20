#ifndef DIVISION_FILELOADER_H
#define DIVISION_FILELOADER_H

#include <string>

namespace Division
{
	struct FileData {
		int width;
		int height;
		int byteCount;
		int rowByteCount;
		unsigned char* rawData;
		unsigned int* colorData;
		bool valid;
	};

	class FileLoader
	{
	public:
		~FileLoader();
		static FileData parseBmp(std::string);
	};
}
#endif // ! DIVISION_FILELOADER_H
