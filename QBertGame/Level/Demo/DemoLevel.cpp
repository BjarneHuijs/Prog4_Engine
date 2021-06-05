#include "QBertGamePCH.h"
#include "../../BuildTypeSelector.h"

#include "DemoLevel.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Structs.h"
#include "SubjectComponent.h"
#include "TextObject.h"
#include "TextObserverComponent.h"
#include "TextureComponent.h"
#include "../../Player/Commands/QBertCommands.h"

void DemoLevel::Load()
{
	using namespace Idiot_Engine;

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	auto texComp = std::make_shared<TextureComponent>("Background");
	texComp->SetTexture("background.jpg");
	go->AddComponent(texComp, texComp->GetName());
	scene.Add(go);

	go = std::make_shared<GameObject>();
	texComp = std::make_shared<TextureComponent>("Logo");
	texComp->SetTexture("logo.png");
	go->AddComponent(texComp, texComp->GetName());
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
	go->AddComponent(fps, fps->GetName());
	go->SetPosition(10, 5);
	scene.Add(go);

	// Lives + Scores
	//	P1
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text = std::make_shared<TextComponent>("Prefix", "P1 ", font, Color{ 0, 255, 0 });
	go->AddComponent(text, text->GetName());
	text->SetRelativePosition(-15, 0);
	text = std::make_shared<TextComponent>("LivesText", "Lives: 3", font, Color{ 0, 255, 0 });
	text->SetRelativePosition(15, 0);
	go->AddComponent(text, text->GetName());
	std::vector<EventTypes> lives{ std::vector<EventTypes>{ EventTypes::LivesChanged } };
	const auto p1LivesObserver = std::make_shared<TextObserverComponent>("Lives", text->GetName(), lives);
	go->AddComponent(p1LivesObserver, p1LivesObserver->GetName());

	// Score
	auto score_1 = std::make_shared<TextComponent>("ScoreText", "Score: 0", font, Color{ 0, 255, 0 });
	go->AddComponent(score_1, score_1->GetName());
	score_1->SetRelativePosition(-15, 40);
	go->SetPosition(20, 110);
	std::vector<EventTypes> score{ std::vector<EventTypes>{ EventTypes::ScoreChanged } };
	const auto p1ScoreObserver = std::make_shared<TextObserverComponent>("Score", score_1->GetName(), score);
	go->AddComponent(p1ScoreObserver, p1ScoreObserver->GetName());
	scene.Add(go);

	m_pQBert_1 = std::make_shared<GameObject>();
	const auto player_1 = std::make_shared<PlayerComponent>("Player 1");
	const auto p1Subject = std::make_shared<SubjectComponent>("Player 1 Subject");
	p1Subject->AddObserver(p1LivesObserver.get());
	p1Subject->AddObserver(p1ScoreObserver.get());
	m_pQBert_1->AddComponent(player_1, player_1->GetName());
	m_pQBert_1->AddComponent(p1Subject, p1Subject->GetName());
	scene.Add(m_pQBert_1);


	//	P2
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text_2 = std::make_shared<TextComponent>("Prefix", "P2 ", font, Color{ 0, 255, 0 });
	go->AddComponent(text_2, text_2->GetName());
	text_2->SetRelativePosition(-15, 0);
	text_2 = std::make_shared<TextComponent>("LivesDisplay", "Lives: 3", font, Color{ 0, 255, 0 });
	text_2->SetRelativePosition(15, 0);
	go->AddComponent(text_2, text_2->GetName());
	const auto p2LivesObserver = std::make_shared<TextObserverComponent>("Lives", text_2->GetName(), lives);
	go->AddComponent(p2LivesObserver, p2LivesObserver->GetName());

	// Score
	auto score_2 = std::make_shared<TextComponent>("ScoreText", "Score: 0", font, Color{ 0, 255, 0 });
	go->AddComponent(score_2, score_2->GetName());
	score_2->SetRelativePosition(-15, 40);
	go->SetPosition(80, 180);
	const auto p2ScoreObserver = std::make_shared<TextObserverComponent>("Score", score_2->GetName(), score);
	go->AddComponent(p2ScoreObserver, p2ScoreObserver->GetName());
	scene.Add(go);

	m_pQBert_2 = std::make_shared<GameObject>();
	const auto player_2 = std::make_shared<PlayerComponent>("Player 2");
	const auto p2Subject = std::make_shared<SubjectComponent>("Player 2 Subject");
	p2Subject->AddObserver(p2LivesObserver.get());
	p2Subject->AddObserver(p2ScoreObserver.get());
	m_pQBert_2->AddComponent(player_2, player_2->GetName());
	m_pQBert_2->AddComponent(p2Subject, p2Subject->GetName());
	scene.Add(m_pQBert_2);


	InitDemoInput(m_pQBert_1.get(), m_pQBert_2.get());

	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	const auto gameEnder = std::make_shared<TextComponent>("DeathText", "  ", font, Color{ 255, 255, 0 });
	std::vector<EventTypes> death{ std::vector<EventTypes>{ EventTypes::PlayerDeath } };
	const auto endObserver = std::make_shared<TextObserverComponent>("Death", gameEnder->GetName(), death);
	go->AddComponent(gameEnder, gameEnder->GetName());
	go->AddComponent(endObserver, endObserver->GetName());
	go->SetPosition(180, 150);
	scene.Add(go);

	p1Subject->AddObserver(endObserver.get());
	p2Subject->AddObserver(endObserver.get());

	// TODO: add more dynamic method to use sound
	auto* audio = ServiceLocator::GetAudio();
#ifdef BUILD
	audio->AddMusic("Data/Star Commander1.wav");
	audio->AddSound("Data/WilhelmScream.WAV");
	audio->AddSound("Data/blaster-shot-single-5.WAV");
	audio->QueueMusic(0);
#endif
#ifdef VS
	audio->AddMusic("../Data/Star Commander1.wav");
	audio->AddSound("../Data/WilhelmScream.WAV");
	audio->AddSound("../Data/blaster-shot-single-5.WAV");
	audio->QueueMusic(0);
#endif
}

void DemoLevel::InitDemoInput(Idiot_Engine::GameObject* controllerObject, Idiot_Engine::GameObject* keyboardObject)
{
	// Init default controller commands
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonA, new KillCoily(controllerObject));
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonX, new ChangeColor(controllerObject));
	InputManager::GetInstance().AddCommand(ControllerButton::ButtonY, new Kill(controllerObject));
	InputManager::GetInstance().AddCommand(ControllerButton::RightShoulder, new CalculateRemainingDiscs(controllerObject));
	//m_ControllerCommands.insert(std::make_pair(ControllerButton::ButtonB, std::make_unique<Fire>(Fire())));
	//m_ControllerCommands.insert(std::make_pair(ControllerButton::ButtonX, std::make_unique<Duck>(Duck())));
	//m_ControllerCommands.insert(std::make_pair(ControllerButton::ButtonY, std::make_unique<Fart>(Fart())));

	// Init default keyboard commands
	//m_KeyboardCommands.insert(std::make_pair('E', std::make_unique<Kill>(Kill(controllerObject))));
	InputManager::GetInstance().AddCommand(SDLK_1, new KillCoily(keyboardObject));
	InputManager::GetInstance().AddCommand(SDLK_2, new ChangeColor(keyboardObject));
	InputManager::GetInstance().AddCommand(SDLK_3, new CatchNPC(keyboardObject));
	InputManager::GetInstance().AddCommand(SDLK_4, new CalculateRemainingDiscs(keyboardObject));
	InputManager::GetInstance().AddCommand(SDLK_e, new Kill(keyboardObject));
}