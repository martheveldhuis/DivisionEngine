#ifndef DIVISION_ENTITY_H
#define DIVISION_ENTITY_H

#include <map>

#include "Resource.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace Division 
{
	class Entity
	{
	public:
		Entity(ResourceManager*, std::string textureFile, std::string meshFile);
		~Entity();
		void addTexture(std::string, Resource*);
		void addMesh(std::string, Resource*);
		Resource* getTexture(std::string);
		Resource* getMesh(std::string);
		void removeTexture(std::string);
		void removeMesh(std::string);
		void render(Renderer*);
	private:
		ResourceManager* resourceManager_;
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Resource*> meshes_;
	};
}

#endif