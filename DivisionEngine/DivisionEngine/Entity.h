#ifndef DIVISION_ENTITY_H
#define DIVISION_ENTITY_H

#include <map>

#include "Resource.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace Division 
{
	struct Position
	{
		float xPosition;
		float yPosition;
		float zPosition;
	};


	class Entity
	{
	public:
		Entity(ResourceManager*, float, float, float);
		virtual ~Entity();
		virtual void addTexture(std::string);
		virtual void addMesh(std::string);
		virtual Resource* getTexture(std::string);
		virtual Resource* getMesh(std::string);
		virtual void removeTexture(std::string);
		virtual void removeMesh(std::string);
		virtual void render(Renderer*) = 0;
	protected:
		ResourceManager* resourceManager_;
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Resource*> meshes_;
		bool isVisible_ = true;
		Position position_;
	};
}

#endif