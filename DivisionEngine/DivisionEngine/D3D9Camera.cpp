#include "D3D9Camera.h"

namespace Division
{
	D3D9Camera::D3D9Camera(ResourceManager* resourceManager, float x, float y, 
						   float z, float xAngle, float yAngle, float zAngle) 
		: Entity(resourceManager, x, y, z, xAngle, yAngle, zAngle)
	{
		clock_ = new Clock();
		clock_->start();
	}



	D3D9Camera::~D3D9Camera()
	{
	}



	void D3D9Camera::updateOrientation(InputStates* inputStates)
	{

		// After multiple rotations, the camera’s axes can become 
		// non-orthogonal(non- perpendicular) to each other (floating point 
		// errors). Therefore, we need to recalculate the up_ and right vectors 
		// based on the look vector using the cross-product. 
		// For easy calculation, normalize(magnitude is 1, direction is kept).
		D3DXVec3Normalize(&right_, &right_);
		D3DXVec3Cross(&up_, &right_, &look_);
		D3DXVec3Normalize(&up_, &up_);
		D3DXVec3Cross(&look_, &up_, &right_);
		D3DXVec3Normalize(&look_, &look_);

		// Check the elapsed time since the last frame.
		clock_t deltaTime = clock_->poll();

		// Scale the movement in the game, based on the time per frame.
		float yawScaling = 5.0 * deltaTime;
		float pitchScaling = 5.0 * deltaTime;
		float velocity = 0.015 * deltaTime;

		// Call the correct methods to alter the camera's vectors and world 
		// matrix based on which input is set. Scale the input values.
		if (inputStates->turnRight) {
			position_.yAngle += (inputStates->turnRight) / yawScaling;
			yaw((inputStates->turnRight) / yawScaling);
		}
		if (inputStates->turnLeft) {
			position_.yAngle -= (inputStates->turnLeft) / yawScaling;
			yaw(-(inputStates->turnLeft) / yawScaling);
		}
		if (inputStates->turnUp) {
			position_.xAngle += (inputStates->turnUp) / pitchScaling;
			// Prevent gimbal lock.
			if (position_.xAngle > 1.55)
				position_.xAngle = 1.55;
			else {
				pitch((inputStates->turnUp) / pitchScaling);
			}
		}
		if (inputStates->turnDown) {
			position_.xAngle -= (inputStates->turnDown) / pitchScaling;
			// Prevent gimbal lock.
			if (position_.xAngle < -1.55)
				position_.xAngle = -1.55;
			else {
				pitch(-(inputStates->turnDown) / pitchScaling);
			}
		}
		if (inputStates->moveForward) {
			walk(velocity);
		}
		if (inputStates->moveBackward) {
			walk(-velocity);
		}
		if (inputStates->moveRight) {
			crabwalk(-velocity);
		}
		if (inputStates->moveLeft) {
			crabwalk(velocity);
		}
		if (inputStates->moveUp) {
			fly(velocity);
		}
		if (inputStates->moveDown) {
			fly(-velocity);
		}

		// Calculate the translation of the camera in the world, taking into
		// account the rotated right, up, and look vectors. The translation of 
		// the camera is negative to the world translation.
		float x = -D3DXVec3Dot(&look_, &pos_);
		float y = -D3DXVec3Dot(&up_, &pos_);
		float z = -D3DXVec3Dot(&right_, &pos_);

		// Matrix lay-out (row-major):
		//
		// rotateLookX		rotateUpX		rotateRightX		0
		// rotateLookY		rotateUpY		rotateRightY		0
		// rotateLookZ		rotateUpZ		rotateRightZ		0
		// translateX		translateY		translateZ			1

		// Build the world matrix.
		world_(0, 0) = look_.x;
		world_(1, 0) = look_.y;
		world_(2, 0) = look_.z;

		world_(0, 1) = up_.x;
		world_(0, 2) = right_.x;
		world_(0, 3) = 0.0f;

		world_(1, 1) = up_.y;
		world_(1, 2) = right_.y;
		world_(1, 3) = 0.0f;

		world_(2, 1) = up_.z;
		world_(2, 2) = right_.z;
		world_(2, 3) = 0.0f;

		world_(3, 0) = x;
		world_(3, 1) = y;
		world_(3, 2) = z;
		world_(3, 3) = 1.0f;
	}



	void D3D9Camera::yaw(float angle)
	{
		D3DXMatrixRotationY(&world_, angle);
		
		// Rotate right and look vectors around y-axis.
		D3DXVec3TransformCoord(&look_, &look_, &world_);
		D3DXVec3TransformCoord(&right_, &right_, &world_);
	}



	void D3D9Camera::pitch(float angle)
	{
		D3DXMatrixRotationAxis(&world_, &right_, angle);

		// Rotate up and look vectors around x-axis.
		D3DXVec3TransformCoord(&up_, &up_, &world_);
		D3DXVec3TransformCoord(&look_, &look_, &world_);
		position_.xAngle = look_.x;
		position_.yAngle = look_.y;
		position_.zAngle = look_.z;
	}



	void D3D9Camera::walk(float units)
	{
		// Add new x, y and z in 'look' direction to position.
		pos_ += D3DXVECTOR3(look_.x, look_.y, look_.z) * units;
		position_.xPosition = pos_.x;
		position_.yPosition = pos_.y;
		position_.zPosition = pos_.z;
	}



	void D3D9Camera::crabwalk(float units)
	{
		// Add new x and z in 'right' direction to position.
		pos_ += D3DXVECTOR3(right_.x, 0.0f, right_.z) * units;
		position_.xPosition = pos_.x;
		position_.zPosition = pos_.z;
	}



	void D3D9Camera::fly(float units)
	{
		// Add new y in 'up' direction to position.
		pos_ += D3DXVECTOR3(0.0f, up_.y, 0.0f) * units;
		position_.yPosition = pos_.y;
	}



	void* D3D9Camera::getOrientation()
	{
		return world_;
	}
}