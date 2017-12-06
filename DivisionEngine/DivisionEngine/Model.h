#ifndef DIVISION_MODEL_H
#define DIVISION_MODEL_H

#include "Entity.h"

namespace Division
{
	class Model : public Entity
	{
	public:
		Model(ResourceManager*, float, float, float);
		~Model();
	};
}

#endif // !DIVISION_MODEL_H