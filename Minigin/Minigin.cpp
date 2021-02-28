#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <objbase.h>

#include "Font.h"
#include "TextObject.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "Scene.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	CoInitialize(nullptr);
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"This engine doesn't know what it's doing",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font, Color{ 255, 0, 0 });
	to->SetPosition(80, 20);
	scene.Add(to);

	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	const auto fps = std::make_shared<FPSComponent>("no fps", font, Color{ 255, 255, 0 });
	go->AddComponent(fps, "FpsCounter");
	go->SetPosition(10, 5);
	scene.Add(go);

	auto p1 = std::make_shared<GameObject>();
	const auto player_1 = std::make_shared<PlayerComponent>();
	p1->AddComponent(player_1, "Player 1");
	scene.Add(p1);

	auto p2 = std::make_shared<GameObject>();
	const auto player_2 = std::make_shared<PlayerComponent>();
	p2->AddComponent(player_2, "Player 2");
	scene.Add(p2);

	InputManager::GetInstance().InitDefaultInput(p1.get(), p2.get());
}

void dae::Minigin::Cleanup()
{
	CoUninitialize();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	LoadGame();
	
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		
		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float lag{ 0.0f };
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float deltaTime{ std::chrono::duration<float>(currentTime - lastTime).count() };

			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			while(lag >= MsPerFrame)
			{
				sceneManager.FixedUpdate(deltaTime);
				lag -= MsPerFrame;
			}
			input.ProcessInput();
			
			sceneManager.Update(deltaTime);
			sceneManager.LateUpdate(deltaTime);
			
			renderer.Render(lag / deltaTime);
			
		}

		input.Clean();
	}

	Cleanup();
}