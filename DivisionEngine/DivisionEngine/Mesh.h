#ifndef DIVISION_MESH_H
#define DIVISION_MESH_H

#include <vector>
#include <map>

#include "Resource.h"
#include "Renderer.h"

namespace Division
{
	/**
		Mesh interface overriding the resource interface.
	*/
	class Mesh : public Resource
	{
	public:
		virtual ~Mesh() {};
		/**
			Sets texture objects on the mesh object. Used by the resource
			manager to set the default textures (that are defined in the loaded
			mesh file) on the mesh.
		*/
		virtual void setTextures(std::map<std::string, Resource*> textures) = 0;
		/**
			Gets the names of the textures file names that belong to the mesh.
			Used by the resource manager to get the default textures file names
			(that are defined in the loaded mesh file).
			@returns A vector containing the texture file names.
		*/
		virtual std::vector<std::string> getTextureFileNames() = 0;
		/**
			Draws the mesh using a renderer and either its default textures, or
			custom ones that are passed to the method.
			@param renderer The renderer used to set materials and textures on.
			@param customTextures Custom textures overriding the default ones.
		*/
		virtual void draw(Renderer* renderer, std::map<std::string, 
						  Resource*> customTextures) = 0;
	};
}

#endif // ! DIVISION_MESH_H