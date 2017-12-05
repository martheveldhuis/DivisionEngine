#ifndef DIVISION_DIVISIONMESH_H
#define DIVISION_DIVISIONMESH_H

#include <vector>

#include "Resource.h"

namespace Division
{
	class DivisionMesh : public Resource
	{
	public:
		virtual ~DivisionMesh() {};
		virtual void setTextures(std::map<std::string, Resource*>) = 0;
		virtual std::vector<std::string> getTextureFileNames() = 0;
		virtual std::map<std::string, Resource*> getTextures() = 0;
	};
}

#endif // ! DIVISION_DIVISIONMESH_H