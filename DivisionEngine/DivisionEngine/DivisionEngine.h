#ifndef DIVISION_DIVISIONENGINE_H
#define DIVISION_DIVISIONENGINE_H

#include "ResourceManager.h"
#include "SceneManager.h"

namespace Division
{
	class DivisionEngine
	{
	public:
		DivisionEngine();
		~DivisionEngine();
		void run();
	private:
		ResourceManager* resourceManager_;
		SceneManager* sceneManager_;
	};
}
#endif