#ifndef DIVISION_CAMERA_H
#define DIVISION_CAMERA_H

#include "Entity.h"
#include "InputDevice.h"

namespace Division
{
	/**
		Special entity that represents a camera. Besides being an entity that
		is renderer within a scene, it is used to calculate the position from
		which the player is looking. 
	*/
	class Camera : public Entity
	{
	public:
		Camera(ResourceManager* rm);
		~Camera();
		/**
			Calculates and updates the location and angles of the camera by 
			interpreting the input provided.
			@param inputStates The struct containing input from the user.
		*/
		void updateCameraPosition(InputStates* inputStates);
		/**
			Gets the current camera position struct.
			@returns The position struct containing the location of the camera.
		*/
		Position* getCameraPosition();
	private:
		float nearClip = 1.0f;
		float farClip = 2000.0f;
	};
}

#endif // !DIVISION_CAMERA_H