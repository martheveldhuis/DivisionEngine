#ifndef DIVISION_SKYBOX_H
#define DIVISION_SKYBOX_H

#include "Entity.h"

namespace Division
{
	class SkyBox : public Entity
	{
	public:
		SkyBox(ResourceManager*, Mesh*, float x = 0, float y = 0, float z = 0,
			float xAngle = 0, float yAngle = 0, float zAngle = 0);
		~SkyBox();
		void render(Renderer*);
	};
}
#endif // ! DIVISION_SKYBOX_H