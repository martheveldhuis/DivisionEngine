#ifndef DIVISION_MODEL_H
#define DIVISION_MODEL_H

#include "Entity.h"

namespace Division
{
	class Model : public Entity
	{
	public:
		Model(ResourceManager*, float x = 0, float y = 0, float z = 0,
			float xAngle = 0, float yAngle = 0, float zAngle = 0);
		~Model();
	};
}

#endif // !DIVISION_MODEL_H