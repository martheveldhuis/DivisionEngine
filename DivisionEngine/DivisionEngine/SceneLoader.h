#ifndef DIVISION_SCENELOADER_H
#define DIVISION_SCENELOADER_H

#include <string>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning
#include <strsafe.h>
#pragma warning( default : 4996 )

#include "Repository.h"
#include "SceneManager.h"
#include "Win32Window.h"

namespace Division
{
	class SceneLoader
	{
	public:
		SceneLoader(SceneManager* sceneManager, Repository*);
		~SceneLoader();
		void loadScene(std::string scene);
		void parseHeightmap(std::string scene, std::string heightMap);

	private:
		Repository* d3D9Repository_ = NULL;
		SceneManager* sceneManager_ = NULL;
	};
}
#endif // ! DIVISION_SCENELOADER_H