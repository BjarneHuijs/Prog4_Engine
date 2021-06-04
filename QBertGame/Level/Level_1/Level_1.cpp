#include "QBertGamePCH.h"
#include "Level_1.h"

#include <fstream>

#include "../../BuildTypeSelector.h"

#include "FPSComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Structs.h"
#include "SubjectComponent.h"
#include "TextObject.h"
#include "TextObserverComponent.h"
#include "TextureComponent.h"
#include "../Tile/Tile.h"

#include "rapidjson.h"
#include "document.h"
#include "reader.h"

void Level_1::Load()
{
	using namespace Idiot_Engine;

	auto& scene = SceneManager::GetInstance().CreateScene("Level_1");

	auto go = std::make_shared<GameObject>();
	auto texComp = std::make_shared<TextureComponent>("Background");
	texComp->SetTexture("background.jpg");
	go->AddComponent(texComp, texComp->GetName());
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
	// FPS
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	const auto fps = std::make_shared<FPSComponent>("FpsCounter", "no fps", font, Color{ 255, 255, 0 });
	go->AddComponent(fps, fps->GetName());
	go->SetPosition(10, 5);
	scene.Add(go);

	SDL_Window* window{ Renderer::GetInstance().GetWindow() };
	int xSize{};
	int ySize{};
	SDL_GetWindowSize(window, &xSize, &ySize);

	m_StartLocation = glm::vec2{ xSize  * 0.45f, ySize / 5 };
	LoadTiles();
	for (const auto tile : m_pTiles)
	{
		scene.Add(tile->GetTileObject());
	}
	
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
	const auto p1LivesObserver = std::make_shared<TextObserverComponent>("Lives", text->GetName(), EventTypes::LivesChanged);
	go->AddComponent(p1LivesObserver, p1LivesObserver->GetName());

	// Score
	auto score_1 = std::make_shared<TextComponent>("ScoreText", "Score: 0", font, Color{ 0, 255, 0 });
	go->AddComponent(score_1, score_1->GetName());
	score_1->SetRelativePosition(-15, 40);
	go->SetPosition(20, 110);
	const auto p1ScoreObserver = std::make_shared<TextObserverComponent>("Score", score_1->GetName(), EventTypes::ScoreChanged);
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


	InputManager::GetInstance().InitDefaultInput(m_pQBert_1.get(), m_pQBert_1.get());

	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	const auto gameEnder = std::make_shared<TextComponent>("DeathText", "  ", font, Color{ 255, 255, 0 });
	const auto endObserver = std::make_shared<TextObserverComponent>("Death", gameEnder->GetName(), EventTypes::PlayerDeath);
	go->AddComponent(gameEnder, gameEnder->GetName());
	go->AddComponent(endObserver, endObserver->GetName());
	go->SetPosition(180, 150);
	scene.Add(go);

	p1Subject->AddObserver(endObserver.get());
	
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

void Level_1::LoadTiles()
{
	using namespace rapidjson;
	Document jsonDoc;
#ifdef BUILD
	std::ifstream file("Data/Level_1.json");
#endif
#ifdef VS
	std::ifstream file("../Data/Level_1.json");
#endif
	std::stringstream buffer{};
	buffer << file.rdbuf();

	jsonDoc.Parse(std::string(buffer.str()).c_str());
	if (jsonDoc.HasMember("tiles"))
	{
		
		const Value& tiles = jsonDoc["tiles"];


		//Check if the data we got has an array
		if (tiles.IsArray())
		{
			//auto size = tiles.Size();
			//auto pos{ m_pTiles.back()->GetTransform().GetPosition() };
			for (Value::ConstValueIterator itr = tiles.Begin(); itr != tiles.End(); ++itr)
			{
				const Value& val = *itr;
				auto idx = val["id"].GetInt();
				std::shared_ptr<Tile> tile = std::make_shared<Tile>(idx);
				m_pTiles.push_back(tile);
			}

		}
		else
		{
			std::cout << "FILE NOT FOUND" << std::endl;
		}

		int rows{ 7 };
		int index{ 0 };
		float xPos{ m_StartLocation.x };
		float yPos{ m_StartLocation.y };
		for (int i{ 1 }; i <= rows; ++i)
		{
			for (int j{ 1 }; j <= i; ++j)
			{
				m_pTiles[index]->SetPosition(xPos, yPos);
				xPos += m_pTiles[0]->GetSize();
				index++;
			}

			if (i % 2 == 0) {
				xPos -= (i + 1) * m_pTiles[0]->GetSize();
				xPos += m_pTiles[0]->GetSize() / 2;
			}
			else 
			{
				xPos -= i * m_pTiles[0]->GetSize();
				xPos -= m_pTiles[0]->GetSize() / 2;
			}
			
			yPos += m_pTiles[0]->GetSize() * 0.85f;
		}
	}
}
