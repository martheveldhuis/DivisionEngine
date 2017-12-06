#ifndef DIVISION_REPOSITORY_H
#define DIVISION_REPOSITORY_H

#include <string>

#include "ResourceLoader.h"
#include "Renderer.h"

namespace Division
{
	class Repository
	{
	public:
		~Repository() {};
		virtual ResourceLoader* getTextureLoader() = 0;
		virtual ResourceLoader* getMeshLoader() = 0;
		virtual Renderer* getRenderer() = 0;
	};
}

#endif // ! DIVISION_REPOSITORY_H