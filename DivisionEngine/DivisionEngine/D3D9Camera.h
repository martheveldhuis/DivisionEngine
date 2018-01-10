#ifndef DIVISION_D3D9CAMERA_H
#define DIVISION_D3D9CAMERA_H

#include <d3dx9.h>

#include "Entity.h"
#include "InputDevice.h"
#include "Clock.h"

namespace Division
{
	/**
		Special entity that represents a Direct 3D specific camera. Besides 
		being an entity that is rendered within a scene, it is used to 
		calculate the position of the player in the scene, handling its 
		movement. This is implemented using Direct 3D methods.
	*/
	class D3D9Camera : public Entity
	{
	public:
		D3D9Camera(ResourceManager* rm, float x = 0, float y = 0, float z = 0,
				   float xAngle = 0, float yAngle = 0, float zAngle = 0);
		~D3D9Camera();
		void updateOrientation(InputStates* inputStates);
		void* getOrientation();
	private:
		/**
			Rotates the camera over the y-axis (up axis).
			@param angle The angle with which to rotate.
		*/
		void yaw(float angle);
		/**
			Rotates the camera over the x-axis (right axis).
			@param angle The angle with which to rotate.
		*/
		void pitch(float angle);
		/**
			Translates the camera position on look axis.
			@param units The amount to move.
		*/
		void walk(float units);
		/**
			Translates the camera position on the right axis.
			@param units The amount to move.
		*/
		void crabwalk(float units);
		/**
			Translates the camera position on the up axis.
			@param units The amount to move.
		*/
		void fly(float units);
		D3DXVECTOR3 look_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	/**< Axis we look at */
		D3DXVECTOR3 up_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		/**< Axis going up/down */
		D3DXVECTOR3 right_ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	/**< Axis going right/left */
		D3DXVECTOR3 pos_;	/**<  Position of the camera */
		D3DXMATRIX world_;	/**<  Orientation of the camera in world space */
		Clock* clock_;
	};
}

#endif // !DIVISION_D3D9CAMERA_H