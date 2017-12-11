#ifndef DIVISION_ENTITY_H
#define DIVISION_ENTITY_H

#include <map>

#include "Mesh.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace Division
{
	class Entity
	{
	public:
		Entity(ResourceManager*, float x = 0, float y = 0, float z = 0,
			float xAngle = 0, float yAngle = 0, float zAngle = 0);
		virtual ~Entity();
		virtual void setTexture(std::string);
		virtual void setMesh(std::string);
		virtual void removeTexture(std::string);
		virtual void removeMesh(std::string);
		virtual void render(Renderer*);
	protected:
		virtual Resource* addTexture(std::string);
		virtual Mesh* addMesh(std::string);
		ResourceManager* resourceManager_;
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Mesh*> meshes_;
		bool isVisible_ = true;
		Position position_;
	};
}

#endif