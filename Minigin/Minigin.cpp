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

	
	Renderer::GetInstance().Init();

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame()
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

	// FPS
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	const auto fps = std::make_shared<FPSComponent>("FpsCounter", "no fps", font, Color{ 255, 255, 0 });
	go->AddComponent(fps, "FpsCounter");
	go->SetPosition(10, 5);
	scene.Add(go);

	// Lives + Scores
	//	P1
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text = std::make_shared<TextComponent>("Prefix", "P1 ", font, Color{ 0, 255, 0 });
	go->AddComponent(text, "Prefix");
	text->SetPosition(-15, 0);
	text = std::make_shared<TextComponent>("LivesDisplay", "Lives: 3", font, Color{ 0, 255, 0 }, EventTypes::LivesChanged);
	text->SetPosition(15, 0);
	go->AddComponent(text, "LivesDisplay");
	// Score
	auto score_1 = std::make_shared<TextComponent>("Score", "Score: 0", font, Color{ 0, 255, 0 }, EventTypes::ScoreChanged);
	go->AddComponent(score_1, "ScoreDisplay");
	score_1->SetPosition(-15, 40);
	go->SetPosition(80, 110);
	scene.Add(go);

	m_pQBert_1 = std::make_shared<GameObject>();
	const auto player_1 = std::make_shared<PlayerComponent>();
	player_1->AddObserver(text.get());
	player_1->AddObserver(score_1.get());
	m_pQBert_1->AddComponent(player_1, "Player 1");
	scene.Add(m_pQBert_1);
	//	P2
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text_2 = std::make_shared<TextComponent>("Prefix", "P2 ", font, Color{ 0, 255, 0 });
	go->AddComponent(text_2, "Prefix");
	text_2->SetPosition(-15, 0);
	text_2 = std::make_shared<TextComponent>("LivesDisplay", "Lives: 3", font, Color{ 0, 255, 0 }, EventTypes::LivesChanged);
	text_2->SetPosition(15, 0);
	go->AddComponent(text_2, "LivesDisplay");
	// Score
	auto score_2 = std::make_shared<TextComponent>("Score", "Score: 0", font, Color{ 0, 255, 0 }, EventTypes::ScoreChanged);
	go->AddComponent(score_2, "ScoreDisplay");
	score_2->SetPosition(-15, 40);
	go->SetPosition(80, 180);
	scene.Add(go);


	m_pQBert_2 = std::make_shared<GameObject>();
	const auto player_2 = std::make_shared<PlayerComponent>();
	player_2->AddObserver(text_2.get());
	player_2->AddObserver(score_2.get());
	m_pQBert_2->AddComponent(player_2, "Player 2");
	scene.Add(m_pQBert_2);

	InputManager::GetInstance().InitDefaultInput(m_pQBert_1.get(), m_pQBert_2.get());

	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	const auto gameEnder = std::make_shared<TextComponent>("DeathText", "  ", font, Color{ 255, 255, 0 }, EventTypes::PlayerDeath);
	go->AddComponent(gameEnder, "DeathText");
	go->SetPosition(180, 150);
	scene.Add(go);

	player_1->AddObserver(gameEnder.get());
	player_2->AddObserver(gameEnder.get());

}

void dae::Minigin::Cleanup()
{
	CoUninitialize();
	Renderer::GetInstance().Destroy();
	//SDL_DestroyWindow(m_Window);
	//m_Window = nullptr;
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

			while(lag >= MsPerFrame)
			{
				sceneManager.FixedUpdate(deltaTime);
				lag -= MsPerFrame;
			}
			doContinue = input.ProcessInput();
			
			sceneManager.Update(deltaTime);
			sceneManager.LateUpdate(deltaTime);
			
			renderer.Render(lag / deltaTime);
			
		}

		input.Clean();
	}

	Cleanup();
}