#pragma once
#include "Command.h"
#include "../QBertComponent.h"
#include "../../Structs_And_Menu/ButtonComponent/ButtonComponent.h"
using namespace Idiot_Engine;
class Kill : public Command
{
public:
	explicit  Kill(GameObject* object) : Command(object) {}
	void Execute() override
	{
		GetActor()->GetComponentByType<QBertComponent>()->Kill();
		//ServiceLocator::GetAudio()->QueueSound(0); // id 0 = kill player
	}
};

class KillCoily : public Command
{
public:
	explicit KillCoily(GameObject* object) : Command(object) {}
	void Execute() override
	{
		GetActor()->GetComponentByType<QBertComponent>()->KillCoilyWithDisc();
		ServiceLocator::GetAudio()->QueueSound(1); // id 1 = kill coily
	}
};

class ChangeColor : public Command
{
public:
	explicit ChangeColor(GameObject* object) : Command(object) {}
	void Execute() override
	{
		GetActor()->GetComponentByType<QBertComponent>()->ChangeColor(0);
	}
};

class CalculateRemainingDiscs : public Command
{
public:
	explicit CalculateRemainingDiscs(GameObject* object) : Command(object) {}
	void Execute() override
	{
		GetActor()->GetComponentByType<QBertComponent>()->RemainingDiscsScore();
	}
};

class CatchNPC : public Command
{
public:
	explicit CatchNPC(GameObject* object) : Command(object) {}
	void Execute() override
	{
		GetActor()->GetComponentByType<QBertComponent>()->CatchNPC();
	}
};

// QBertMovement
class MoveTopLeft : public Command
{
public:
	explicit MoveTopLeft(GameObject* object) : Command(object) {}
	void Execute() override { GetActor()->GetComponentByType<QBertComponent>()->MoveTopLeft(); };
};

class MoveTopRight : public Command
{
public:
	explicit MoveTopRight(GameObject* object) : Command(object) {}
	void Execute() override { GetActor()->GetComponentByType<QBertComponent>()->MoveTopRight(); }
};

class MoveBotLeft : public Command
{
public:
	explicit MoveBotLeft(GameObject* object) : Command(object) {}
	void Execute() override { GetActor()->GetComponentByType<QBertComponent>()->MoveBotLeft(); }
};

class MoveBotRight : public Command
{
public:
	explicit MoveBotRight(GameObject* object) : Command(object) {}
	void Execute() override { GetActor()->GetComponentByType<QBertComponent>()->MoveBotRight(); }
};

// Menu Commands
class MoveSelectionUp : public Command
{
public:
	explicit MoveSelectionUp(GameObject* object) : Command(object) {}
	void Execute() override
	{
		const std::string selectedButton{ GetActor()->GetComponentByType<ButtonComponent>()->GetSelectedButtonName() };
		GetActor()->GetComponentByName<ButtonComponent>(selectedButton)->MoveSelectionUp();
	}
};

class MoveSelectionDown : public Command
{
public:
	explicit MoveSelectionDown(GameObject* object) : Command(object) {}
	void Execute() override
	{
		const std::string selectedButton{ GetActor()->GetComponentByType<ButtonComponent>()->GetSelectedButtonName() };
		GetActor()->GetComponentByName<ButtonComponent>(selectedButton)->MoveSelectionDown();
	}
};

class ConfirmSelection : public Command
{
public:
	explicit ConfirmSelection(GameObject* object) : Command(object) {}
	void Execute() override
	{
		const std::string selectedButton{ GetActor()->GetComponentByType<ButtonComponent>()->GetSelectedButtonName() };
		if(selectedButton._Equal("StartGameButton"))
		{
			SceneManager::GetInstance().SetActiveScene("Level_1");
			GetActor()->GetComponentByName<ButtonComponent>(selectedButton)->GetUser()->StartNewGame();
			//GetActor()->GetComponentByName<ButtonComponent>(selectedButton)->GetUser2()->StartNewGame(false);
		}
		else if(selectedButton._Equal("MainMenuButton"))
		{
			SceneManager::GetInstance().SetActiveScene("MainMenu");
		}
		else if(selectedButton._Equal("CoopButton"))
		{
			/*GetActor()->GetComponentByName<ButtonComponent>(selectedButton)->GetUser()->StartNewGame(true);
			GetActor()->GetComponentByName<ButtonComponent>(selectedButton)->GetUser2()->StartNewGame(true);
			SceneManager::GetInstance().SetActiveScene("Level_1");*/
		}
		else if (selectedButton._Equal("ExitGameButton"))
		{
			InputManager::GetInstance().QuitGame();
		}
	}
};