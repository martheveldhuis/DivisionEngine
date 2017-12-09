#ifndef DIVISION_REPOSITORY_H
#define DIVISION_REPOSITORY_H

#include <string>

#include "ResourceLoader.h"
#include "Renderer.h"
#include "Entity.h"

namespace Division
{
	class Repository
	{
	public:
		~Repository() {};
		virtual void* getFrameworkInterface() = 0;
		virtual ResourceLoader* getTextureLoader() = 0;
		virtual ResourceLoader* getMeshLoader() = 0;
		virtual Renderer* getRenderer() = 0;
		virtual Entity* parseHeightmap(std::string, ResourceManager*) = 0;
	};
}

#endif // ! DIVISION_REPOSITORY_H