#ifndef DIVISION_MESH_H
#define DIVISION_MESH_H

#include <vector>
#include <map>

#include "Resource.h"
#include "Renderer.h"

namespace Division
{
	class Mesh : public Resource
	{
	public:
		virtual ~Mesh() {};
		virtual void setTextures(std::map<std::string, Resource*>) = 0;
		virtual std::vector<std::string> getTextureFileNames() = 0;
		virtual std::map<std::string, Resource*> getTextures() = 0;
		virtual int getNumberOfMaterials() = 0;
		virtual void draw(Renderer*, std::map<std::string, Resource*>) = 0;
	};
}

#endif // ! DIVISION_MESH_H