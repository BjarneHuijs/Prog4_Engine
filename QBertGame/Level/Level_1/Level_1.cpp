#include "QBertGamePCH.h"
#include "Level_1.h"

#include <fstream>

#include "document.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "rapidjson.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SpriteComponent.h"
#include "Structs.h"
#include "SubjectComponent.h"
#include "TextObserverComponent.h"
#include "TextureComponent.h"
#include "../../BuildTypeSelector.h"
#include "../../Player/QBertComponent.h"
#include "../../Player/Commands/QBertCommands.h"
#include "../../Player/Observer/PlayerObserverComponent.h"
#include "../Tile/TileComponent.h"

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
	LoadTiles(scene);
	
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
	const auto player_1 = std::make_shared<QBertComponent>("Player 1", this);
	const auto playerSprite = std::make_shared<SpriteComponent>("Player 1 Sprite", 8);
	playerSprite->SetScale(2, 2);
	playerSprite->SetTexture("QBert.png");
	const auto p1Subject = std::make_shared<SubjectComponent>("Player 1 Subject");
	p1Subject->AddObserver(p1LivesObserver.get());
	p1Subject->AddObserver(p1ScoreObserver.get());
	m_pQBert_1->AddComponent(player_1, player_1->GetName());
	m_pQBert_1->AddComponent(p1Subject, p1Subject->GetName());
	m_pQBert_1->AddComponent(playerSprite, playerSprite->GetName());
	std::vector<EventTypes> moves{ std::vector<EventTypes>{ EventTypes::MoveTopLeft, EventTypes::MoveTopRight, EventTypes::MoveBotLeft, EventTypes::MoveBotRight } };
	const auto moveObserver = std::make_shared<PlayerObserverComponent>("Move", player_1->GetName(), moves);
	scene.Add(m_pQBert_1);

	const float posOffset{ m_pTiles[0].size * 0.25f };
	player_1->SetPosOffset(posOffset);
	m_pQBert_1->SetPosition(m_StartLocation.x + posOffset, m_StartLocation.y - posOffset);


	InputManager::GetInstance().AddCommand(SDLK_w, new MoveTopLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(ControllerButton::DPadUp, new MoveTopLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(SDLK_d, new MoveTopRight(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(ControllerButton::DPadRight, new MoveTopRight(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(SDLK_a, new MoveBotLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(ControllerButton::DPadLeft, new MoveBotLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(SDLK_s, new MoveBotRight(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(ControllerButton::DPadDown, new MoveBotRight(m_pQBert_1.get()));

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

void Level_1::LoadTiles(Scene& scene)
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

			m_pTileObjects = std::vector<std::shared_ptr<GameObject>>();
			m_pTiles = std::vector<TileData>();
			//Nr of frames in tile sprite: 8
			int NrOfTileFrames{ 8 };
			for (Value::ConstValueIterator itr = tiles.Begin(); itr != tiles.End(); ++itr)
			{
				const Value& val = *itr;
				// -1 to start from 0
				auto idx = val["id"].GetInt();

				std::vector<int> moveTiles = LoadLinkedTiles(val, "LinkedPlayTiles");
				std::vector<int> sideMoveTiles = LoadLinkedTiles(val, "LinkedSideTiles");
								
				std::shared_ptr<GameObject> tileObject(std::make_shared<GameObject>());
				//std::shared_ptr<TileComponent> tile = std::make_shared<TileComponent>(idx, moveTiles, sideMoveTiles);
				std::shared_ptr<SpriteComponent> tileSprite = std::make_shared<SpriteComponent>("Tile_" + std::to_string(idx) + "_Sprite", NrOfTileFrames);
				const auto tileSubject = std::make_shared<SubjectComponent>("Tile " + std::to_string(idx) + " Subject");
				tileSprite->SetTexture("Tiles.png");
				//tileObject->AddComponent(tile, tile->GetName());
				tileObject->AddComponent(tileSprite, tileSprite->GetName());
				tileObject->AddComponent(tileSubject, tileSubject->GetName());

				TileData tileData
				{
					idx,
					{},
					moveTiles[0],
					moveTiles[1],
					moveTiles[2],
					moveTiles[3],
					sideMoveTiles[0],
					sideMoveTiles[1]
				};
				m_pTiles.push_back(tileData);
				
				//std::shared_ptr<TileComponent> tile = std::make_shared<TileComponent>(idx);
				m_pTileObjects.push_back(tileObject);
				scene.Add(tileObject);
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
		float tileSize{ m_pTiles[0].size };
		for (int i{ 1 }; i <= rows; ++i)
		{
			for (int j{ 1 }; j <= i; ++j)
			{
				m_pTileObjects[index]->SetPosition(xPos, yPos);
				m_pTiles[index].Position = m_pTileObjects[index]->GetTransform();
				xPos += tileSize;
				index++;
			}

			if (i % 2 == 0) {
				xPos -= (i + 1) * tileSize;
				xPos += tileSize / 2;
			}
			else 
			{
				xPos -= i * tileSize;
				xPos -= tileSize / 2;
			}
			
			yPos += tileSize * 0.85f;
		}
	}
}

std::vector<TileData> Level_1::GetTiles() const
{
	return m_pTiles;
}

using namespace rapidjson;
std::vector<int> Level_1::LoadLinkedTiles(const Value& val, const std::string& jsonKey) const
{
	const Value& jsonArray = val[jsonKey.c_str()];
	std::vector<int> array{};
	
	if (jsonArray.IsArray())
	{
		for (Value::ConstValueIterator itr = jsonArray.Begin(); itr != jsonArray.End(); ++itr)
		{
			const Value& link = *itr;
			int value{ link.GetInt() };
			array.push_back(value);
		}
	}

	return array;
}
