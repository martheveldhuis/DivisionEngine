#include "Model.h"

namespace Division
{
	Model::Model(ResourceManager* rm, 
		float x, float y, float z, 
		float xAngle, float yAngle, float zAngle)
		: Entity(rm, x, y, z, xAngle, yAngle, zAngle)
	{
	}


	Model::~Model()
	{
	}
}
