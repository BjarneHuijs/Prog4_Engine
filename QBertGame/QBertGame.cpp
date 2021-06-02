#include "QBertGamePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "BuildTypeSelector.h"

#include "Minigin.h"
#include "ResourceManager.h"
#include "Level/Test.h"

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
	LoadGame();

	engine.Run();

	
	return 0;
}

void LoadGame()
{
	Test t{};
	t.Load();
	//t.Load2();
}