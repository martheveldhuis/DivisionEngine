#include "SkyBox.h"
#include "d3dx9.h"

namespace Division
{
	SkyBox::SkyBox(ResourceManager* rm, Mesh* mesh,
			float x, float y, float z,
			float xAngle, float yAngle, float zAngle)
		: Entity(rm, x, y, z, xAngle, yAngle, zAngle)
	{
		meshes_["skybox"] = mesh;
	}



	SkyBox::~SkyBox()
	{
	}



	void SkyBox::render(Renderer* renderer)
	{
		std::map<std::string, Mesh*>::const_iterator meshIterator = meshes_.begin();
		while (meshIterator != meshes_.end()) {
			renderer->setWorldMatrix(&position_);
			meshIterator->second->draw(renderer, textures_);
			++meshIterator;
		}
	}
}