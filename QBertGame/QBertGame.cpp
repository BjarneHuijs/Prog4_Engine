#include "QBertGamePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "BuildTypeSelector.h"

#include "Minigin.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Level/Demo/DemoLevel.h"
#include "Level/Level_1/Level_1.h"

void LoadGame();


int main(int, char* [])
{
	Idiot_Engine::Minigin engine;
	engine.Initialize();
	
	// tell the resource manager where he can find the game data
	// 
#ifdef VS
	Idiot_Engine::ResourceManager::GetInstance().Init("../Data/");
#endif
#ifdef BUILD
	Idiot_Engine::ResourceManager::GetInstance().Init("Data/");
#endif
	
	//TODO 1: make menu scene and menu nav
	//TODO 2: make Level scene accessed from menu (read from file)
	//TODO 3: back to menu scene after game
	//LoadGame();
	Level_1 t{};
	Idiot_Engine::SceneManager::GetInstance().SetActiveScene("Level_1");

	engine.Run();

	
	return 0;
}
