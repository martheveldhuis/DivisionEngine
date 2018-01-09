#ifndef DIVISION_ENTITY_H
#define DIVISION_ENTITY_H

#include <map>

#include "Mesh.h"
#include "ResourceManager.h"
#include "InputDevice.h"


namespace Division
{
	class Renderer;

	/**
		The class that defines entities. Entities are things that need to be
		rendered in a scene. They have a position in that scene and have 
		resources with which they are rendered.
	*/
	class Entity
	{
	public:
		/**
			Constructs an entity with a default '0' position.
			@param resourceManager The provider of resources.
			@param x The x location of the entity, default 0.
			@param y The y location of the entity, default 0.
			@param z The z location of the entity, default 0.
			@param x The x angle of the entity, default 0.
			@param y The y angle of the entity, default 0.
			@param z The z angle of the entity, default 0.
		*/
		Entity(ResourceManager* resourceManager, 
			   float x = 0, float y = 0, float z = 0,
			   float xAngle = 0, float yAngle = 0, float zAngle = 0);
		virtual ~Entity();
		/**
			Sets a texture object on the textures_ map based on the texture's 
			file name. Requests the object from the resourcemanager.
			@param textureFile The file name of the texture.
		*/
		virtual void setTexture(std::string textureFile);
		/**
			Sets a mesh object on the meshes_ map based on the mesh's 
			file name. Requests the object from the resourcemanager.
			@param meshFile The file name of the mesh.
		*/
		virtual void setMesh(std::string meshFile);
		/**
			Removes a texture object from the textures_ map based on the 
			texture's file name. The texture object will also be deleted in 
			the resource manager.
			@param textureFile The file name of the texture.
		*/
		virtual void removeTexture(std::string textureFile);
		/**
			Removes a mesh object from the meshes_ map based on the mesh's file
			name. The mesh object will also be deleted in the resource manager.
			@param meshFile The file name of the mesh.
		*/
		virtual void removeMesh(std::string);
		/**
			Loops through all the mesh objects on the entity and draws them
			using the given renderer and texture objects.
			@param renderer The renderer to use for drawing the entity.
		*/
		virtual void render(Renderer* renderer);
		/**
			Calculates and updates the location and angles of the entity by 
			interpreting the input provided.
			@param inputStates The struct containing input from the user.
		*/
		virtual void updateOrientation(InputStates* inputStates);
		/**
			Gets the current entity world orientation, which contains
			information about how the entity is rotated, translated and
			scaled within the world.
			@returns The entity world matrix.
		*/
		virtual void* getOrientation();
	protected:
		virtual Resource* addTexture(std::string);
		virtual Mesh* addMesh(std::string);
		ResourceManager* resourceManager_;
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Mesh*> meshes_;
		Position position_;
		bool isVisible_ = true;
	};
}

#endif