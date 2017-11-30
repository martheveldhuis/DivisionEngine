#include "Scene.h"
namespace Division {
	Scene::Scene()
	{
	}

	Scene::Scene(ResourceManager * rm, Renderer* renderer) : resourceManager_(rm)
	{
		// this should come from the ??heightmaploader??


		const int width = 34;
		const int lenght = 34;

	    CUSTOMVERTEX* vertices = new CUSTOMVERTEX[width * lenght];

		int index = 0;
		

		for (int i = width / 2; i > -(width / 2); i--) {
			for (int j = -(lenght / 2); j < lenght / 2; j++) {
				// maak random height value
				float x = (rand() % 300) / 100.0f; //max = 3.0

				// maak grijswaarde gebaseerd op height val
				DWORD grayValB = int(x) * 80;
				DWORD grayValG = (int(x) * 80) << 8;
				DWORD grayValR = (int(x) * 80) << 16;
				int grayColor = grayValR + grayValG + grayValB;

				vertices[index++] = { static_cast<float>(i), x/2, static_cast<float>(j), 0xff000000 + grayColor };
			}
		}

		addRenderer("main", renderer);
		terrain_ = new Terrain(vertices, renderer, index);
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