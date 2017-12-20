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
			position_.zPosition += 0.08f;
		}
		if (inputStates->moveBackward) {
			position_.zPosition -= 0.08f;
		}
		if (inputStates->moveRight) {
			position_.xPosition += 0.08f;
		}
		if (inputStates->moveLeft) {
			position_.xPosition -= 0.08f;
		}
		if (inputStates->turnRight) {
			position_.yAngle += (inputStates->turnRight)/100.0f;
		}
		if (inputStates->turnLeft) {
			position_.yAngle -= (inputStates->turnLeft)/100.0f;
		}
	}

	Position* Camera::getCameraPosition()
	{
		return &position_;
	}
}