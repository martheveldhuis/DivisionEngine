#ifndef DIVISION_RESOURCELOADER_H
#define DIVISION_RESOURCELOADER_H

#include <string>

#include "Resource.h"

namespace Division
{
	/**
		Interface for every type of resource loader for use by the resource
		manager.
	*/
	class ResourceLoader
	{
	public:
		virtual ~ResourceLoader() {};
		/**
			Creates a resource object from data in the specified file.
			@param resourceName The file from which to create the resource.
			@returns A resource object based on the given file.
		*/
		virtual Resource* getResource(std::string resourceName) = 0;
	};
}

#endif // !DIVISION_RESOURCELOADER_H