#include "Camera.h"

namespace Division
{
	Camera::Camera(ResourceManager* rm) : Entity(rm)
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::updateCameraPosition(InputStates* inputStates)
	{
		if (inputStates->moveForward) {
			position.zPosition += 0.08f;
		}
		if (inputStates->moveBackward) {
			position.zPosition -= 0.08f;
		}
		if (inputStates->moveRight) {
			position.xPosition += 0.08f;
		}
		if (inputStates->moveLeft) {
			position.xPosition -= 0.08f;
		}
		if (inputStates->turnRight) {
			position.yAngle += (inputStates->turnRight)/100.0f;
		}
		if (inputStates->turnLeft) {
			position.yAngle -= (inputStates->turnLeft)/100.0f;
		}
	}

	Position Camera::getCameraPosition()
	{
		return position;
	}
}