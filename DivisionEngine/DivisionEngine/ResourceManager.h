#ifndef DIVISION_RESOURCEMANAGER_H
#define DIVISION_RESOURCEMANAGER_H

#include <map>
#include <string>

#include "ResourceLoader.h"
#include "Resource.h"
#include "Mesh.h"

namespace Division
{
	/**	
		Manages all resource objects such as textures and meshes. Creates
		these resources with loaders which are provided when it is made by the
		kernel. Is used by entities to get resources.
	 */
	class ResourceManager
	{
	public:
		/**
			@param textureLoader The resource loader to create texture objects.
			@param meshLoader The resource loader to create mesh objects.   
		*/
		ResourceManager(ResourceLoader* textureLoader, 
			ResourceLoader* meshLoader);
		~ResourceManager();
		/**
			Gets a texture object from the textures map, based on the 
			texture's file name. If it does not exist, create that texture
			object with its texture loader.
		 	@param textureFile The file name of the desired texture.
		 	@returns A resource reference to the desired texture.
		 */	
		Resource* getTexture(std::string textureFile);
		/**
			Gets a mesh object from the meshes map, based on the mesh's file
			name. If it does not exist, create that mesh object with its mesh 
			loader.
			@param meshFile The file name of the desired mesh.
			@returns A mesh reference to the desired mesh.
		*/
		Mesh* getMesh(std::string meshFile);
		/**
			Removes a texture object from the textures map, based on the
			texture's file name. 
			@param textureFile The file name of the texture.
		*/
		void removeTexture(std::string textureFile);
		/**
			Removes a mesh object from the mesh map, based on the mesh's file
			name.
			@param meshFile The file name of the mesh.
		*/
		void removeMesh(std::string meshFile);
		/**
			@returns The number of textures saved on the resource manager.
		*/
		int getNumberOfTextures();
		/**
			@returns The number of meshes saved on the resource manager.
		*/
		int getNumberOfMeshes();
	private:
		Resource* addNewTexture(std::string);
		Resource* addNewMesh(std::string);
		ResourceLoader* textureLoader_;
		ResourceLoader* meshLoader_;
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Resource*> meshes_;
	};
}
#endif