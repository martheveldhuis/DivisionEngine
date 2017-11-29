#ifndef DIVISION_ENTITY_H
#define DIVISION_ENTITY_H

#include "Resource.h"
#include "ResourceManager.h"

#include <map>
namespace Division {
	class Entity
	{
	private:
		std::map<std::string, Resource*> resources_;
		ResourceManager* resourceManager_;

	public:
		Entity();
		Entity(ResourceManager*);
		~Entity();

		void addResource(std::string, Resource*);
		void getResource(std::string, Resource*);
		void removeResource(std::string);
	};
}
#endif