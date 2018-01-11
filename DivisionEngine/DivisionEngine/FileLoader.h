#ifndef DIVISION_FILELOADER_H
#define DIVISION_FILELOADER_H

#include <string>

namespace Division
{
	struct FileData {
		int width;               /** The width of the image in pixels */
		int height;				 /** The width of the image in pixels */
		int byteCount;           /** The bytes per pixel */
		int rowByteCount;        /** The bytes per row including padding */
		unsigned char* rawData;  /** The raw data, directly read from the file */
		unsigned int* colorData; /** The calculated color values, aggrigated per pixel */
		bool valid;              /** Whether or not the file was valid (successfully read) */
	};

	/**
		Parses file types into usable array's and formats. Each file type has
		its own function. Currently this function is not capable of detecting
		file type. In future releases the response type should be provided to
		determine what format should be returned. Then, the file extension can
		be used to choose the parse function.
	*/
	class FileLoader
	{
	public:
		~FileLoader();
		/**
			Parses a BMP file and retrieves a FileData struct filled with the
			found data.
			@returns Struct with the data and meta-data of the parsed image.
		*/
		static FileData parseBmp(std::string);
	};
}
#endif // ! DIVISION_FILELOADER_H
