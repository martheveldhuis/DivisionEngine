#include "Scene.h"
namespace Division
{
	Scene::Scene(ResourceManager * rm) : resourceManager_(rm)
	{
		//// this should come from the ??heightmaploader??

		//const int width = 30;
		//const int lenght = 30;

		//CUSTOMVERTEX* vertices = new CUSTOMVERTEX[width * lenght];

		//int index = 0;

		//srand(GetTickCount64());
		//for (int i = 0; i < width; i++) {
		//	for (int j = 0; j < lenght; j++) {
		//		// maak random height value
		//		float y = (rand() % 300) / 100.0f; //max = 3.0

		//										   // maak grijswaarde gebaseerd op height val
		//		DWORD grayValB = int(y) * 80;
		//		DWORD grayValG = (int(y) * 80) << 8;
		//		DWORD grayValR = (int(y) * 80) << 16;
		//		int grayColor = grayValR + grayValG + grayValB;
		//		int x = i - width / 2 + 1;
		//		int z = j - lenght / 2 + 1;
		//		index = i * width + j;
		//		vertices[index] = { static_cast<float>(x), -y / 4 - .5f, static_cast<float>(z), 0xff000000 + grayColor };
		//	}
		//}
	}

	Scene::~Scene()
	{
	}

	void Scene::render()
	{
		std::map<std::string, DivisionWindow>::iterator it_windows;
		for (it_windows = windows_.begin(); it_windows != windows_.end(); it_windows++)
		{
			void* whandle = it_windows->second.window->getWindowHandle();
			it_windows->second.renderer->setHandle(whandle);

			std::map<std::string, DivisionEntity>::iterator it_entity;
			for (it_entity = entities_.begin(); it_entity != entities_.end(); it_entity++)
			{
				if (it_entity->second.window == it_windows->second.window)
				{
					it_entity->second.entity->render(it_windows->second.renderer);
				}
			}
		}
	}

	void Scene::addWindow(std::string str, DivisionWindow win)
	{
		windows_[str] = win;
	}

	DivisionWindow* Scene::getWindow(std::string str)
	{
		std::map<std::string, DivisionWindow>::iterator it;
		it = windows_.find(str);
		if (it != windows_.end())
			return &it->second;
		else
			return nullptr;
	}

	void Scene::removeWindow(std::string str)
	{
		std::map<std::string, DivisionWindow>::iterator it;
		it = windows_.find(str);
		if (it != windows_.end())
		{
			delete it->second.window;
			//it->second.renderer.decreaseReference(); //TODO add call too refrence count decreaser of renderer.
			windows_.erase(it);
		}
	}

	void Scene::addEntity(std::string str, DivisionEntity ent)
	{
		entities_[str] = ent;
	}

	//std::pair<Entity*, Window*>* Scene::createEntity(std::string str, Window* win)
	//{
	//	std::pair<Entity*, Window*> ent = std::pair<Entity*, Window*>(new Entity(resourceManager_, 0, 0, 0), win);
	//	entities_[str] = ent;
	//	return &ent;
	//}

	DivisionEntity* Scene::getEntity(std::string str)
	{
		std::map<std::string, DivisionEntity>::iterator it;
		it = entities_.find(str);
		return nullptr;
	}

	void Scene::removeEntity(std::string str)
	{
		std::map<std::string, DivisionEntity>::iterator it;
		it = entities_.find(str);
		if (it != entities_.end())
		{
			delete it->second.entity;
			//it->second.window.decreaseReference(); //TODO add call too refrence count decreaser of window.
			entities_.erase(it);
		}
	}
}