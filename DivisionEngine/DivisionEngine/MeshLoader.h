#ifndef DIVISION_MESHLOADER_H
#define DIVISION_MESHLOADER_H

#include <string>

#include "ResourceLoader.h"
#include "Mesh.h"

namespace Division
{
	class MeshLoader : public ResourceLoader
	{
	public:
		/**
		@param direct3DDevice The d3d9 device necessary to create d3d9
		mesh data from a file.	
		*/
		~MeshLoader() {};
		virtual Mesh* getResource(std::string resourceName) = 0;
		virtual Mesh* getSkyBox() = 0;
	};
}

#endif // !DIVISION_MESHLOADER_H