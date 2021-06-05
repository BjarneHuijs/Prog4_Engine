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

#include "TextObject.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "Scene.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "SubjectComponent.h"
#include "TextObserverComponent.h"
#include "TextureComponent.h"

using namespace std;
using namespace std::chrono;

void Idiot_Engine::Minigin::Initialize()
{
	CoInitialize(nullptr);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	//basic default values (may/will change later) => might fail for specific audio files/formats
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 8, 2048);
	const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
	if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
	{
		throw std::runtime_error(std::string("SDL_Mixer_Init Error: ") + SDL_GetError());
	}

	SDLSoundSystem* audioService = new SDLSoundSystem{};
	ServiceLocator::RegisterAudioService(audioService);
	
	Renderer::GetInstance().Init();

}

/**
 * Code constructing the scene world starts here
 */
void Idiot_Engine::Minigin::LoadGame()
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<GameObject>();
	//auto texComp = std::make_shared<TextureComponent>("Background");
	//texComp->SetTexture("background.jpg");
	//go->AddComponent(texComp, texComp->GetName());
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//texComp = std::make_shared<TextureComponent>("Logo");
	//texComp->SetTexture("logo.png");
	//go->AddComponent(texComp, texComp->GetName());
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font, Color{ 255, 0, 0 });
	//to->SetPosition(80, 20);
	//scene.Add(to);

	//// FPS
	//go = std::make_shared<GameObject>();
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//const auto fps = std::make_shared<FPSComponent>("FpsCounter", "no fps", font, Color{ 255, 255, 0 });
	//go->AddComponent(fps, fps->GetName());
	//go->SetPosition(10, 5);
	//scene.Add(go);

	//// Lives + Scores
	////	P1
	//go = std::make_shared<GameObject>();
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//auto text = std::make_shared<TextComponent>("Prefix", "P1 ", font, Color{ 0, 255, 0 });
	//go->AddComponent(text, text->GetName());
	//text->SetRelativePosition(-15, 0);
	//text = std::make_shared<TextComponent>("LivesText", "Lives: 3", font, Color{ 0, 255, 0 });
	//text->SetRelativePosition(15, 0);
	//go->AddComponent(text, text->GetName());
	//const auto p1LivesObserver = std::make_shared<TextObserverComponent>("Lives", text->GetName(), EventTypes::LivesChanged);
	//go->AddComponent(p1LivesObserver, p1LivesObserver->GetName());
	//
	//// Score
	//auto score_1 = std::make_shared<TextComponent>("ScoreText", "Score: 0", font, Color{ 0, 255, 0 });
	//go->AddComponent(score_1, score_1->GetName());
	//score_1->SetRelativePosition(-15, 40);
	//go->SetPosition(80, 110);
	//const auto p1ScoreObserver = std::make_shared<TextObserverComponent>("Score", score_1->GetName(), EventTypes::ScoreChanged);
	//go->AddComponent(p1ScoreObserver, p1ScoreObserver->GetName());
	//scene.Add(go);

	//m_pQBert_1 = std::make_shared<GameObject>();
	//const auto player_1 = std::make_shared<PlayerComponent>("Player 1");
	//const auto p1Subject = std::make_shared<SubjectComponent>("Player 1 Subject");
	//p1Subject->AddObserver(p1LivesObserver.get());
	//p1Subject->AddObserver(p1ScoreObserver.get());
	//m_pQBert_1->AddComponent(player_1, player_1->GetName());
	//m_pQBert_1->AddComponent(p1Subject, p1Subject->GetName());
	//scene.Add(m_pQBert_1);

	//
	////	P2
	//go = std::make_shared<GameObject>();
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	//auto text_2 = std::make_shared<TextComponent>("Prefix", "P2 ", font, Color{ 0, 255, 0 });
	//go->AddComponent(text_2, text_2->GetName());
	//text_2->SetRelativePosition(-15, 0);
	//text_2 = std::make_shared<TextComponent>("LivesDisplay", "Lives: 3", font, Color{ 0, 255, 0 });
	//text_2->SetRelativePosition(15, 0);
	//go->AddComponent(text_2, text_2->GetName());
	//const auto p2LivesObserver = std::make_shared<TextObserverComponent>("Lives", text_2->GetName(), EventTypes::LivesChanged);
	//go->AddComponent(p2LivesObserver, p2LivesObserver->GetName());
	//
	//// Score
	//auto score_2 = std::make_shared<TextComponent>("ScoreText", "Score: 0", font, Color{ 0, 255, 0 });
	//go->AddComponent(score_2, score_2->GetName());
	//score_2->SetRelativePosition(-15, 40);
	//go->SetPosition(80, 180);
	//const auto p2ScoreObserver = std::make_shared<TextObserverComponent>("Score", score_2->GetName(), EventTypes::ScoreChanged);
	//go->AddComponent(p2ScoreObserver, p2ScoreObserver->GetName());
	//scene.Add(go);

	//m_pQBert_2 = std::make_shared<GameObject>();
	//const auto player_2 = std::make_shared<PlayerComponent>("Player 2");
	//const auto p2Subject = std::make_shared<SubjectComponent>("Player 2 Subject");
	//p2Subject->AddObserver(p2LivesObserver.get());
	//p2Subject->AddObserver(p2ScoreObserver.get());
	//m_pQBert_2->AddComponent(player_2, player_2->GetName());
	//m_pQBert_2->AddComponent(p2Subject, p2Subject->GetName());
	//scene.Add(m_pQBert_2);

	//
	//InputManager::GetInstance().InitDemoInput(m_pQBert_1.get(), m_pQBert_2.get());

	//go = std::make_shared<GameObject>();
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	//const auto gameEnder = std::make_shared<TextComponent>("DeathText", "  ", font, Color{ 255, 255, 0 });
	//const auto endObserver = std::make_shared<TextObserverComponent>("Death", gameEnder->GetName(), EventTypes::PlayerDeath);
	//go->AddComponent(gameEnder, gameEnder->GetName());
	//go->AddComponent(endObserver, endObserver->GetName());
	//go->SetPosition(180, 150);
	//scene.Add(go);

	//p1Subject->AddObserver(endObserver.get());
	//p2Subject->AddObserver(endObserver.get());

	//// TODO: add more dynamic method to use sound
	//auto* audio = ServiceLocator::GetAudio();
	//audio->AddMusic("../Data/Star Commander1.wav");
	//audio->AddSound("../Data/WilhelmScream.WAV");
	//audio->AddSound("../Data/blaster-shot-single-5.WAV");

	//audio->QueueMusic(0);
}

void Idiot_Engine::Minigin::Cleanup()
{
	CoUninitialize();

	// Safe shutdown for audio
	Mix_CloseAudio();
	Mix_Quit();
	
	ServiceLocator::Cleanup();
	//InputManager::GetInstance().Clean();
	Renderer::GetInstance().Destroy();
	//SDL_DestroyWindow(m_Window);
	//m_Window = nullptr;
	SDL_Quit();
}

void Idiot_Engine::Minigin::Run()
{
	//Initialize();
	// tell the resource manager where he can find the game data
	//ResourceManager::GetInstance().Init("../Data/");
	//LoadGame();
	
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
				sceneManager.FixedUpdate(MsPerFrame);
				lag -= MsPerFrame;
			}
			
			doContinue = input.ProcessInput();
			
			sceneManager.Update(deltaTime);
			sceneManager.LateUpdate(deltaTime);
			
			renderer.Render(deltaTime);
			
		}

	}

	Cleanup();
}