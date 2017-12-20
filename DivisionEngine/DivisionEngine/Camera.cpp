#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>

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
		if (inputStates->turnRight) {
			position_.yAngle += (inputStates->turnRight) / 100.0f;
		}
		if (inputStates->turnLeft) {
			position_.yAngle -= (inputStates->turnLeft) / 100.0f;
		}
		if (inputStates->turnUp) {
			position_.xAngle += (inputStates->turnUp) / 100.0f;
		}
		if (inputStates->turnDown) {
			position_.xAngle -= (inputStates->turnDown) / 100.0f;
		}
		if (inputStates->moveForward) {
			position_.zPosition += cos(position_.yAngle) * 0.1f;
			position_.xPosition += sin(position_.yAngle) * 0.1f;
		}
		if (inputStates->moveBackward) {
			position_.zPosition -= cos(position_.yAngle) * 0.1f;
			position_.xPosition -= sin(position_.yAngle) * 0.1f;
		}
		if (inputStates->moveRight) {
			position_.zPosition += cos(position_.yAngle + M_PI / 2) * 0.1f;
			position_.xPosition += sin(position_.yAngle + M_PI / 2) * 0.1f;
		}
		if (inputStates->moveLeft) {
			position_.zPosition -= cos(position_.yAngle + M_PI / 2) * 0.1f;
			position_.xPosition -= sin(position_.yAngle + M_PI / 2) * 0.1f;
		}
	}

	Position Camera::getCameraPosition()
	{
		return position_;
	}
}