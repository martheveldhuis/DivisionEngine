#ifndef DIVISION_RESOURCELOADER_H
#define DIVISION_RESOURCELOADER_H

#include <string>

#include "Resource.h"

namespace Division
{
	class ResourceLoader
	{
	public:
		virtual ~ResourceLoader() = 0 {};
		virtual Resource* getResource(std::string, void*) = 0;
	};
}

#endif // !DIVISION_RESOURCELOADER_H