#ifndef DIVISION_D3D9GAMEOBJECT_H
#define DIVISION_D3D9GAMEOBJECT_H

#include <d3d9.h>

#include "Entity.h"
#include "D3D9Renderer.h"
#include "D3D9Mesh.h"
#include "D3D9Texture.h"

namespace Division
{
	class D3D9GameObject : public Entity
	{
	public:
		D3D9GameObject(ResourceManager*, float, float, float);
		~D3D9GameObject();
		virtual void render(Renderer*);
	};
}

#endif // !DIVISION_D3D9GAMEOBJECT_H