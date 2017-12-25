#include "D3D9Camera.h"

namespace Division
{
	D3D9Camera::D3D9Camera(ResourceManager* resourceManager) : Entity(resourceManager)
	{
	}



	D3D9Camera::~D3D9Camera()
	{
	}



	void D3D9Camera::updateCameraPosition(InputStates* inputStates)
	{

		// After multiple rotations, the camera’s axes can become 
		// non-orthogonal(non- perpendicular) to each other (floating point 
		// errors). Therefore, we need to recalculate the up and right vectors 
		// based on the look vector using the cross-product. 
		// For easy calculation, normalize(magnitude is 1, direction is kept).
		D3DXVec3Normalize(&right, &right);
		D3DXVec3Cross(&up, &right, &look);
		D3DXVec3Normalize(&up, &up);
		D3DXVec3Cross(&look, &up, &right);
		D3DXVec3Normalize(&look, &look);
		
		// Call the correct methods to alter the camera's vectors and world 
		// matrix based on which input is set. Scale the input values.
		if (inputStates->turnRight) {
			position_.yAngle += (inputStates->turnRight) / 100.0f;
			yaw((inputStates->turnRight) / 100.0f);
		}
		if (inputStates->turnLeft) {
			position_.yAngle -= (inputStates->turnLeft) / 100.0f;
			yaw(-(inputStates->turnLeft) / 100.0f);
		}
		if (inputStates->turnUp) {
			position_.xAngle += (inputStates->turnUp) / 500.0f;
			pitch((inputStates->turnUp) / 500.0f);
		}
		if (inputStates->turnDown) {
			position_.xAngle -= (inputStates->turnDown) / 500.0f;
			pitch(-(inputStates->turnDown) / 500.0f);
		}
		if (inputStates->moveForward) {
			position_.zPosition += inputStates->moveForward * 0.1f;
			walk(inputStates->moveForward * 0.1f);
		}
		if (inputStates->moveBackward) {
			position_.zPosition -= inputStates->moveForward * 0.1f;
			walk(-inputStates->moveBackward * 0.1f);
		}
		if (inputStates->moveRight) {
			position_.xPosition -= inputStates->moveRight * 0.1f;
			crabwalk(-inputStates->moveRight * 0.1f);
		}
		if (inputStates->moveLeft) {
			position_.xPosition += inputStates->moveRight * 0.1f;
			crabwalk(inputStates->moveLeft * 0.1f);
		}

		// Calculate the translation of the camera in the world, taking into
		// account the rotated right, up, and look vectors. The translation of 
		// the camera is negative to the world translation.
		float x = -D3DXVec3Dot(&look, &pos);
		float y = -D3DXVec3Dot(&up, &pos);
		float z = -D3DXVec3Dot(&right, &pos);

		// Matrix lay-out (row-major):
		//
		// rotateLookX		rotateUpX		rotateRightX		0
		// rotateLookY		rotateUpY		rotateRightY		0
		// rotateLookZ		rotateUpZ		rotateRightZ		0
		// translateX		translateY		translateZ			1

		// Build the world matrix.
		world(0, 0) = look.x;
		world(1, 0) = look.y;
		world(2, 0) = look.z;

		world(0, 1) = up.x;
		world(0, 2) = right.x;
		world(0, 3) = 0.0f;

		world(1, 1) = up.y;
		world(1, 2) = right.y;
		world(1, 3) = 0.0f;

		world(2, 1) = up.z;
		world(2, 2) = right.z;
		world(2, 3) = 0.0f;

		world(3, 0) = x;
		world(3, 1) = y;
		world(3, 2) = z;
		world(3, 3) = 1.0f;
	}



	void D3D9Camera::yaw(float angle)
	{
		D3DXMatrixRotationY(&world, angle);
		
		// Rotate right and look vectors around y-axis.
		D3DXVec3TransformCoord(&look, &look, &world);
		D3DXVec3TransformCoord(&right, &right, &world);
	}



	void D3D9Camera::pitch(float angle)
	{
		D3DXMatrixRotationAxis(&world, &right, angle);

		// Rotate up and look vectors around x-axis.
		D3DXVec3TransformCoord(&up, &up, &world);
		D3DXVec3TransformCoord(&look, &look, &world);
	}



	void D3D9Camera::walk(float units)
	{
		// Add new x and z in 'look' direction to position.
		pos += D3DXVECTOR3(look.x, 0.0f, look.z) * units;
	}



	void D3D9Camera::crabwalk(float units)
	{
		// Add new x and z in 'right' direction to position.
		pos += D3DXVECTOR3(right.x, 0.0f, right.z) * units;
	}



	void* D3D9Camera::getCameraOrientation()
	{
		return world;
	}
}