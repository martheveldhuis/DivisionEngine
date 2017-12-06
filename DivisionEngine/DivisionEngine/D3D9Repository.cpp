#include "D3D9Repository.h"

namespace Division
{
	D3D9Repository::D3D9Repository()
	{
	}

	ResourceLoader* D3D9Repository::getTextureLoader()
	{
		return nullptr;
	}

	ResourceLoader* D3D9Repository::getMeshLoader()
	{
		return nullptr;
	}

	Renderer* D3D9Repository::getRenderer()
	{
		return new D3D9Renderer(nullptr, nullptr, nullptr);
	}


	D3D9Repository::~D3D9Repository()
	{
	}
}