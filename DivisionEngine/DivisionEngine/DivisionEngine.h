#ifndef DIVISION_DIVISIONENGINE_H
#define DIVISION_DIVISIONENGINE_H

#include "ResourceManager.h"
#include "SceneManager.h"
namespace Division {
	class DivisionEngine
	{
	private:
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;

	public:
		DivisionEngine();
		~DivisionEngine();

		void getResourceManager(ResourceManager*);
		void getSceneManager(SceneManager*);
	};
}
#endif