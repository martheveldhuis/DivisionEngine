#ifndef DIVISION_D3D9CAMERA_H
#define DIVISION_D3D9CAMERA_H

#include <d3dx9.h>

#include "Entity.h"
#include "InputDevice.h"

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
		D3D9Camera(ResourceManager* rm);
		~D3D9Camera();
		/**
			Calculates and updates the location and angles of the camera by 
			interpreting the input provided.
			@param inputStates The struct containing input from the user.
		*/
		void updateCameraPosition(InputStates* inputStates);
		/**
			Gets the current camera world orientation, which contains
			information about how the camera is rotated, translated and
			scaled within the world.
			@returns The camera world matrix.
		*/
		void* getCameraOrientation();
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
		D3DXVECTOR3 look = D3DXVECTOR3(1.0f, 0.0f, 0.0f);	/**< Axis we look at */
		D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		/**< Axis going up/down */
		D3DXVECTOR3 right = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	/**< Axis going right/left */
		D3DXVECTOR3 pos;	/**<  Position of the camera */
		D3DXMATRIX world;	/**<  Orientation of the camera in world space */
	};
}

#endif // !DIVISION_D3D9CAMERA_H