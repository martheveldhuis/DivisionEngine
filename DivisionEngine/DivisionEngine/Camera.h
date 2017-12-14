#ifndef DIVISION_CAMERA_H
#define DIVISION_CAMERA_H

#include "Entity.h"
#include "InputDevice.h"

namespace Division
{
	class Camera : public Entity
	{
	public:
		Camera(ResourceManager* rm);
		~Camera();
		void updateCameraPosition(InputStates* inputStates);
		Position getCameraPosition();
	private:
		Position position = { 0, 0, 0, 0, 0, 0 };
		float nearClip = 1.0f;
		float farClip = 2000.0f;
	};
}

#endif // !DIVISION_CAMERA_H