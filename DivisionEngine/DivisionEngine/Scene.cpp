#include "Scene.h"
namespace Division {
	Scene::Scene()
	{
	}

	Scene::Scene(ResourceManager * rm, Renderer* renderer) : resourceManager_(rm)
	{
		// this should come from the ??heightmaploader??


		const int width = 10;
		const int lenght = 10;

	    CUSTOMVERTEX* vertices = new CUSTOMVERTEX[width * lenght];

		int index = 0;
	

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < lenght; j++) {
				// maak random height value
				float y = (rand() % 300) / 100.0f; //max = 3.0

												   // maak grijswaarde gebaseerd op height val
				DWORD grayValB = int(y) * 80;
				DWORD grayValG = (int(y) * 80) << 8;
				DWORD grayValR = (int(y) * 80) << 16;
				int grayColor = grayValR + grayValG + grayValB;
				int x = i - width / 2 + 1;
				int z = j - lenght / 2 + 1;
				index = i * width + j;
				vertices[index] = { static_cast<float>(x), y/2, static_cast<float>(z), 0xff000000 + grayColor };
			}
		}


		addRenderer("main", renderer);
		terrain_ = new Terrain(vertices, renderer, width * lenght);
	}

	Scene::~Scene()
	{
	}

	void Scene::addWindow(std::string str, Window* window)
	{
		windows_[str] = window;
	}

	void Scene::getWindow(std::string str, Window* window)
	{
		window = windows_.find(str)->second;
	}

	void Scene::removeWindow(std::string str)
	{
		windows_.erase(windows_.find(str));
	}

	void Scene::addRenderer(std::string name, Renderer* renderer)
	{
		renderers_[name] = renderer;
	}

	void Scene::getRenderer(std::string name, Renderer* renderer)
	{
		renderer = renderers_.find(name)->second;
	}

	void Scene::removeRenderer(std::string name)
	{
		renderers_.erase(renderers_.find(name));
	}
	void Scene::begin()
	{
		terrain_->render();
	}
}