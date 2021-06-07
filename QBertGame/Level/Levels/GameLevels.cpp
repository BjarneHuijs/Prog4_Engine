#include "QBertGamePCH.h"
#include "GameLevels.h"

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
#include "../../NPC/Observer/NPCObserverComponent.h"
#include "../../NPC/Spawner/SpawnerComponent.h"
#include "../../Player/QBertComponent.h"
#include "../../Player/Commands/QBertCommands.h"
#include "../../Player/Observer/PlayerObserverComponent.h"
#include "../../Structs_And_Menu/ButtonComponent/ButtonComponent.h"
#include "../Tile/TileManager.h"

GameLevels::GameLevels()
{
	InitAudio();
	InitQBert();
	LoadMainMenu();
	LoadEndMenu();
	LoadLevel(1);
	LoadLevel(2);
	LoadLevel(3);
	m_pQBert_1->GetComponentByType<QBertComponent>()->SetCurrentLevel(1);
	SceneManager::GetInstance().SetActiveScene("MainMenu");
}

void GameLevels::LoadMainMenu()
{
	using namespace Idiot_Engine;
	auto& scene = SceneManager::GetInstance().CreateScene("MainMenu");

	auto go = std::make_shared<GameObject>();
	auto texComp = std::make_shared<TextureComponent>("Background");
	texComp->SetTexture("background.jpg");
	go->AddComponent(texComp, texComp->GetName());
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	SDL_Window* window{ Renderer::GetInstance().GetWindow() };
	int xSize{};
	int ySize{};
	SDL_GetWindowSize(window, &xSize, &ySize);

	auto title = std::make_shared<TextComponent>("MenuText", "QBert", font, Color{ 255, 255, 0 });
	go->AddComponent(title, title->GetName());
	title->SetRelativePosition((xSize * 0.4f), 50);

	scene.Add(go);

	scene.Add(m_pQBert_1);

	m_pButtonObject = std::make_shared<GameObject>();
	const auto startGame = std::make_shared<ButtonComponent>("StartGameButton", this);
	m_pButtonObject->AddComponent(startGame, startGame->GetName());
	const auto startButtonTex = std::make_shared<TextureComponent>("StartGameButton_Texture");
	startButtonTex->SetScale(0.5f, 0.3f);
	startButtonTex->SetRelativePosition(0, 100);
	m_pButtonObject->AddComponent(startButtonTex, startButtonTex->GetName());


	const auto quitGame = std::make_shared<ButtonComponent>("ExitGameButton", this);
	m_pButtonObject->AddComponent(quitGame, quitGame->GetName());
	const auto quitButtonTex = std::make_shared<TextureComponent>("ExitGameButton_Texture");
	quitButtonTex->SetScale(0.5f, 0.3f);
	quitButtonTex->SetRelativePosition(0, 200);
	m_pButtonObject->AddComponent(quitButtonTex, quitButtonTex->GetName());

	startGame->SetNextButton(quitGame->GetName());
	startGame->SetPreviousButton(quitGame->GetName());
	
	m_pButtonObject->SetPosition(xSize * 0.25f, 80);
	scene.Add(m_pButtonObject);
	
	quitGame->DeSelect();
	startGame->Select();
	
	InitMenuInput("MainMenu");
}

void GameLevels::LoadEndMenu()
{
	using namespace Idiot_Engine;
	auto& scene = SceneManager::GetInstance().CreateScene("EndMenu");

	auto go = std::make_shared<GameObject>();
	auto texComp = std::make_shared<TextureComponent>("Background");
	texComp->SetTexture("background.jpg");
	go->AddComponent(texComp, texComp->GetName());
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	SDL_Window* window{ Renderer::GetInstance().GetWindow() };
	int xSize{};
	int ySize{};
	SDL_GetWindowSize(window, &xSize, &ySize);
	
	auto score_1 = std::make_shared<TextComponent>("ScoreText", "Score: 0", font, Color{ 0, 255, 0 });
	go->AddComponent(score_1, score_1->GetName());
	score_1->SetRelativePosition((xSize * 0.4f), 170);

	std::vector<EventTypes> score{ std::vector<EventTypes>{ EventTypes::ScoreChanged } };
	const auto p1ScoreObserver = std::make_shared<TextObserverComponent>("Score", score_1->GetName(), score);
	go->AddComponent(p1ScoreObserver, p1ScoreObserver->GetName());
	scene.Add(go);

	auto p1Subject = m_pQBert_1->GetComponentByType<SubjectComponent>();
	p1Subject->AddObserver(p1ScoreObserver.get());
	scene.Add(m_pQBert_1);
	m_pQBert_1->SetPosition(xSize / 2.f, ySize / 2.f);
	
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	const auto gameEnder = std::make_shared<TextComponent>("DeathText", "  ", font, Color{ 255, 255, 0 });
	std::vector<EventTypes> death{ std::vector<EventTypes>{ EventTypes::PlayerDeath } };
	const auto endObserver = std::make_shared<TextObserverComponent>("Death", gameEnder->GetName(), death);
	go->AddComponent(gameEnder, gameEnder->GetName());
	go->AddComponent(endObserver, endObserver->GetName());
	go->SetPosition(xSize * 0.4f, 120);
	scene.Add(go);

	p1Subject->AddObserver(endObserver.get());


	m_pButtonObject = std::make_shared<GameObject>();
	const auto mainMenu = std::make_shared<ButtonComponent>("MainMenuButton", this);
	m_pButtonObject->AddComponent(mainMenu, mainMenu->GetName());
	const auto startButtonTex = std::make_shared<TextureComponent>("MainMenuButton_Texture");
	startButtonTex->SetScale(0.5f, 0.3f);
	startButtonTex->SetRelativePosition(0, 220);
	m_pButtonObject->AddComponent(startButtonTex, startButtonTex->GetName());

	mainMenu->SetPreviousButton(mainMenu->GetName());

	m_pButtonObject->SetPosition(xSize * 0.25f, 80);
	scene.Add(m_pButtonObject);

	mainMenu->Select();
	
	InitMenuInput("EndMenu");
}

void GameLevels::LoadLevel(int levelNum)
{
	using namespace Idiot_Engine;
	std::string levelName{ "Level_" + std::to_string(levelNum) };
	auto& scene = SceneManager::GetInstance().CreateScene(levelName);
	
	auto go = std::make_shared<GameObject>();
	auto texComp = std::make_shared<TextureComponent>("Background");
	texComp->SetTexture("background.jpg");
	go->AddComponent(texComp, texComp->GetName());
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	
#ifdef VS
	// FPS
	go = std::make_shared<GameObject>();
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	const auto fps = std::make_shared<FPSComponent>("FpsCounter", "no fps", font, Color{ 255, 255, 0 });
	go->AddComponent(fps, fps->GetName());
	go->SetPosition(10, 5);
	scene.Add(go);
#endif
	
	SDL_Window* window{ Renderer::GetInstance().GetWindow() };
	int xSize{};
	int ySize{};
	SDL_GetWindowSize(window, &xSize, &ySize);

	
	m_StartLocation = glm::vec2{ xSize  * 0.45f, ySize / 5 };
#ifdef BUILD
	std::ifstream file("Data/Levels/" + levelName + ".json");
#endif
#ifdef VS
	std::ifstream file("../Data/Levels/" + levelName + ".json");
#endif
	LoadTiles(scene, file);

	go = std::make_shared<GameObject>();
	const auto spawner = std::make_shared<SpawnerComponent>("npcSpawner", m_SpawnerInterval);
	std::vector<NPCTypes> types{};
	switch (m_NrOfNPCTypes)
	{
		case 1:
			types.push_back(NPCTypes::Slime);
			break;
		case 2:
			types.push_back(NPCTypes::Slime);
			types.push_back(NPCTypes::Coily);
			break;
		case 3:
			types.push_back(NPCTypes::Slime);
			types.push_back(NPCTypes::SlickSam);
			types.push_back(NPCTypes::Coily);
			break;
		default: 
			types.push_back(NPCTypes::Slime);
			types.push_back(NPCTypes::SlickSam);
			types.push_back(NPCTypes::Coily);
			types.push_back(NPCTypes::UggWrong);
			break;
	}
	spawner->SetNpcTypes(types);
	go->AddComponent(spawner, spawner->GetName());
	scene.Add(go);
	
	// Lives + Scores
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

	auto player_1 = m_pQBert_1->GetComponentByType<QBertComponent>();
	auto p1Subject = m_pQBert_1->GetComponentByType<SubjectComponent>();
	p1Subject->AddObserver(p1LivesObserver.get());
	p1Subject->AddObserver(p1ScoreObserver.get());
	scene.Add(m_pQBert_1);
	
	const float posOffset{ m_pTiles[0]->size * 0.25f };
	m_pQBert_1->GetComponentByType<QBertComponent>()->SetPosOffset(posOffset);
	m_pQBert_1->SetPosition(m_StartLocation.x + posOffset, m_StartLocation.y - posOffset);
	
	
	for(size_t idx{}; idx < m_pTileObjects.size(); idx++)
	{
		std::vector<EventTypes> moveEvents{ EventTypes::TileChanged };
		std::string observerName{ "Tile " + std::to_string(idx) + " Level " + std::to_string(levelNum) + " Observer" };
		const auto playerObserver = std::make_shared<PlayerObserverComponent>(observerName, player_1->GetName(), moveEvents, levelNum);
		m_pTileObjects[idx]->AddComponent(playerObserver, playerObserver->GetName());
		p1Subject->AddObserver(playerObserver.get());
	}

	for(size_t idx{}; idx < m_pDiscObjects.size(); idx++)
	{
		std::vector<EventTypes> moveEvents{ EventTypes::DiscChanged };
		std::string observerName{ "Disc " + std::to_string(idx) + " Level " + std::to_string(levelNum) + " Observer" };
		const auto playerObserver = std::make_shared<PlayerObserverComponent>(observerName, player_1->GetName(), moveEvents, levelNum);
		m_pDiscObjects[idx]->AddComponent(playerObserver, playerObserver->GetName());
		p1Subject->AddObserver(playerObserver.get());
	}

	//go = std::make_shared<GameObject>();
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	//const auto gameEnder = std::make_shared<TextComponent>("DeathText", "  ", font, Color{ 255, 255, 0 });
	//std::vector<EventTypes> death{ std::vector<EventTypes>{ EventTypes::PlayerDeath } };
	//const auto endObserver = std::make_shared<TextObserverComponent>("Death", gameEnder->GetName(), death);
	//go->AddComponent(gameEnder, gameEnder->GetName());
	//go->AddComponent(endObserver, endObserver->GetName());
	//go->SetPosition(180, 150);
	//scene.Add(go);

	//p1Subject->AddObserver(endObserver.get());
	
	// TODO: add more dynamic method to use sound
	auto* audio = ServiceLocator::GetAudio();
	audio->QueueMusic(0);

	InitGameplayInput(levelName);
}

void GameLevels::LoadTiles(Scene& scene, const std::ifstream& file)
{
	using namespace rapidjson;
	Document jsonDoc;

	std::stringstream buffer{};
	buffer << file.rdbuf();

	jsonDoc.Parse(std::string(buffer.str()).c_str());
	if (jsonDoc.HasMember("Tiles"))
	{
		int lvlNr = jsonDoc["LevelNr"].GetInt();
		int nrOfColors = jsonDoc["NrOfColors"].GetInt();
		m_SpawnerInterval = jsonDoc["SpawnInterval"].GetInt();
		m_NrOfNPCTypes = jsonDoc["NrOfNPCtypes"].GetInt();
		
		const Value& tiles = jsonDoc["Tiles"];

		//Check if the data we got has an array
		if (tiles.IsArray())
		{
			//auto size = tiles.Size();
			//auto pos{ m_pTiles.back()->GetTransform().GetPosition() };

			m_pTileObjects = std::vector<std::shared_ptr<GameObject>>();
			
			//Nr of frames in tile sprite: 8
			int NrOfTileFrames{ 8 };
			//std::string playerName{ m_pQBert_1->GetComponentByType<QBertComponent>()->GetName() };
			for (Value::ConstValueIterator itr = tiles.Begin(); itr != tiles.End(); ++itr)
			{
				const Value& val = *itr;
				// -1 to start from 0
				auto idx = val["Id"].GetInt();

				std::vector<int> moveTiles = LoadLinkedTiles(val, "LinkedPlayTiles");
				std::vector<int> sideMoveTiles = LoadLinkedTiles(val, "LinkedSideTiles");
								
				std::shared_ptr<GameObject> tileObject(std::make_shared<GameObject>());
				//std::shared_ptr<TileComponent> tile = std::make_shared<TileComponent>(idx, moveTiles, sideMoveTiles);
				std::shared_ptr<SpriteComponent> tileSprite = std::make_shared<SpriteComponent>("TileSprite_" + std::to_string(idx), NrOfTileFrames);
				//tileObject->AddComponent(tile, tile->GetName());
				tileObject->AddComponent(tileSprite, tileSprite->GetName());

				tileSprite->SetTexture("Tiles.png");
				TileData* tileData = new TileData
				{
					idx,
					{},
					moveTiles[0],
					moveTiles[1],
					moveTiles[2],
					moveTiles[3],
					sideMoveTiles[0],
					sideMoveTiles[1],

					TileStates::Base,
					lvlNr,
					nrOfColors
				};
				tileSprite->ToTargetFrame((lvlNr - 1) * tileData->FramesPerLevel);

				TileManager::GetInstance().AddTile(tileData);
				
				
				//m_pTiles.push_back(tileData);
				
				//std::shared_ptr<TileComponent> tile = std::make_shared<TileComponent>(idx);
				m_pTileObjects.push_back(tileObject);
				scene.Add(tileObject);
			}

			if (jsonDoc.HasMember("Discs"))
			{
				const Value& discs = jsonDoc["Discs"];
				//Check if the data we got has an array
				if (discs.IsArray())
				{
					//auto size = tiles.Size();
					//auto pos{ m_pTiles.back()->GetTransform().GetPosition() };

					m_pDiscObjects = std::vector<std::shared_ptr<GameObject>>();
					
					//Nr of frames in disc sprite: 2
					int NrOfDiscFrames{ 2 };
					//std::string playerName{ m_pQBert_1->GetComponentByType<QBertComponent>()->GetName() };
					for (Value::ConstValueIterator itr = discs.Begin(); itr != discs.End(); ++itr)
					{
						const Value& val = *itr;
						// -1 to start from 0
						auto idx = val["Id"].GetInt();

						int connectedTile = val["ConnectedTile"].GetInt();
						int targetTile = val["TargetTile"].GetInt();

						std::shared_ptr<GameObject> discObject(std::make_shared<GameObject>());
						std::shared_ptr<SpriteComponent> tileSprite = std::make_shared<SpriteComponent>("DiscSprite_" + std::to_string(idx), NrOfDiscFrames);
						tileSprite->SetScale(2, 2);
						discObject->AddComponent(tileSprite, tileSprite->GetName());

						tileSprite->SetTexture("Disc.png");
						DiscData* discData = new DiscData
						{
							idx,
							{},
							connectedTile,
							targetTile,
							TileStates::Base,
							lvlNr,
							nrOfColors,
						};
						tileSprite->ToTargetFrame(0);

						TileManager::GetInstance().AddDisc(discData);
						m_pDiscObjects.push_back(discObject);
						scene.Add(discObject);
					}
				}
			}
		}
		else
		{
			std::cout << "FILE NOT FOUND" << std::endl;
		}

		m_pTiles = TileManager::GetInstance().GetTiles(lvlNr - 1);
		
		int rows{ 7 };
		int index{ 0 };
		float xPos{ m_StartLocation.x };
		float yPos{ m_StartLocation.y };
		float tileSize{ m_pTiles[0]->size };
		for (int i{ 1 }; i <= rows; ++i)
		{
			for (int j{ 1 }; j <= i; ++j)
			{
				m_pTileObjects[index]->SetPosition(xPos, yPos);
				m_pTiles[index]->Position = m_pTileObjects[index]->GetTransform();
				
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

		m_pDiscs = TileManager::GetInstance().GetDiscs(lvlNr - 1);
		size_t nrOfTiles{ m_pTiles.size() };
		size_t nrOfDiscs{ m_pDiscs.size() };
		for (size_t i{ 0 }; i < nrOfTiles; ++i) 
		{
			for (size_t j{ 0 }; j < nrOfDiscs; ++j)
			{
				if (m_pDiscs[j]->ConnectedTile == m_pTiles[i]->TileID)
				{
					if (m_pTiles[i]->TopLeft == -1)
					{
						xPos = m_pTiles[i]->Position.GetPosition2D().x;
						yPos = m_pTiles[i]->Position.GetPosition2D().y;
						
						m_pDiscObjects[j]->SetPosition(xPos - (tileSize * 0.25f), yPos - (tileSize * 0.5f));
						m_pDiscs[j]->Position = m_pDiscObjects[j]->GetTransform();
					}
					else if (m_pTiles[i]->TopRight == -1)
					{
						xPos = m_pTiles[i]->Position.GetPosition2D().x;
						yPos = m_pTiles[i]->Position.GetPosition2D().y;
						
						m_pDiscObjects[j]->SetPosition(xPos + (tileSize * 0.75f), yPos - (tileSize * 0.5f));
						m_pDiscs[j]->Position = m_pDiscObjects[j]->GetTransform();
					}
				}
			}
		}
	}
}

using namespace rapidjson;
std::vector<int> GameLevels::LoadLinkedTiles(const Value& val, const std::string& jsonKey) const
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

void GameLevels::InitAudio()
{
	//Music
	// id 0 = bgm
	
	// Sounds:
	// id 0 = loss life
	// id 1 = jump player
	// id 2 = jump enemy
	// id 3 = jump slime
	// id 4 = fall
	// id 5 = lift
	// id 6 = level done
	// id 7 = Game over
	// id 8 = swear
	
	auto* audio = ServiceLocator::GetAudio();
#ifdef BUILD
	audio->AddMusic("Data/Audio/Star Commander1.wav");
	audio->AddSound("Data/Audio/WilhelmScream.WAV"); // id 0
	audio->AddSound("Data/Audio/jump-qbert.mp3"); // id 1
	audio->AddSound("Data/Audio/jump-npc.mp3"); // id 2
	audio->AddSound("Data/Audio/jump-slime.mp3"); // id 3
	audio->AddSound("Data/Audio/fall.mp3"); // id 4
	audio->AddSound("Data/Audio/lift.mp3"); // id 5
	audio->AddSound("Data/Audio/tune-levelClear.mp3"); // id 6
	audio->AddSound("Data/Audio/tune-gameOver.mp3"); // id 7
	audio->AddSound("Data/Audio/swear.mp3"); // id 8
#endif
#ifdef VS
	audio->AddMusic("../Data/Audio/Star Commander1.wav");
	audio->AddSound("../Data/Audio/WilhelmScream.WAV"); // id 0
	audio->AddSound("../Data/Audio/jump-qbert.mp3"); // id 1
	audio->AddSound("../Data/Audio/jump-npc.mp3"); // id 2
	audio->AddSound("../Data/Audio/jump-slime.mp3"); // id 3
	audio->AddSound("../Data/Audio/fall.mp3"); // id 4
	audio->AddSound("../Data/Audio/lift.mp3"); // id 5
	audio->AddSound("../Data/Audiotune-levelClear.mp3"); // id 6
	audio->AddSound("../Data/Audio/tune-gameOver.mp3"); // id 7
	audio->AddSound("../Data/Audio/swear.mp3"); // id 8
#endif   
}

void GameLevels::InitGameplayInput(const std::string& levelName)
{
	InputManager::GetInstance().AddCommand(levelName, SDLK_w, new MoveTopLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(levelName, ControllerButton::DPadUp, new MoveTopLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(levelName, SDLK_d, new MoveTopRight(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(levelName, ControllerButton::DPadRight, new MoveTopRight(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(levelName, SDLK_a, new MoveBotLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(levelName, ControllerButton::DPadLeft, new MoveBotLeft(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(levelName, SDLK_s, new MoveBotRight(m_pQBert_1.get()));
	InputManager::GetInstance().AddCommand(levelName, ControllerButton::DPadDown, new MoveBotRight(m_pQBert_1.get()));
}

void GameLevels::InitMenuInput(const std::string& levelName)
{
	InputManager::GetInstance().AddCommand(levelName, SDLK_w, new MoveSelectionUp(m_pButtonObject.get()));
	InputManager::GetInstance().AddCommand(levelName, ControllerButton::DPadUp, new MoveSelectionUp(m_pButtonObject.get()));

	InputManager::GetInstance().AddCommand(levelName, SDLK_s, new MoveSelectionDown(m_pButtonObject.get()));
	InputManager::GetInstance().AddCommand(levelName, ControllerButton::DPadDown, new MoveSelectionDown(m_pButtonObject.get()));

	InputManager::GetInstance().AddCommand(levelName, SDLK_RETURN, new ConfirmSelection(m_pButtonObject.get()));
	InputManager::GetInstance().AddCommand(levelName, ControllerButton::ButtonA, new ConfirmSelection(m_pButtonObject.get()));
}

void GameLevels::InitQBert()
{
	m_pQBert_1 = std::make_shared<GameObject>();
	const auto player_1 = std::make_shared<QBertComponent>("Player 1");
	const auto playerSprite = std::make_shared<SpriteComponent>("Player 1 Sprite", 8);
	playerSprite->SetScale(2, 2);
	playerSprite->SetTexture("QBert.png");
	const auto p1Subject = std::make_shared<SubjectComponent>("Player 1 Subject");

	m_pQBert_1->AddComponent(player_1, player_1->GetName());
	m_pQBert_1->AddComponent(p1Subject, p1Subject->GetName());
	m_pQBert_1->AddComponent(playerSprite, playerSprite->GetName());
}

std::shared_ptr<QBertComponent> GameLevels::GetQBert() const
{
	return m_pQBert_1->GetComponentByType<QBertComponent>();
}
