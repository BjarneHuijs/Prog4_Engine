#pragma once

//#include "Windows.h"
#include "Xinput.h"
#pragma comment (lib, "XInput.lib")
#include <map>

#include "Singleton.h"
#include <memory>
#include <SDL.h>
#include <vector>

namespace Idiot_Engine
{
	enum ControllerButton
	{
		ButtonA = VK_PAD_A,
		ButtonB = VK_PAD_B,
		ButtonX = VK_PAD_X,
		ButtonY = VK_PAD_Y,
		DPadUp = VK_PAD_DPAD_UP,
		DPadLeft = VK_PAD_DPAD_LEFT,
		DPadRight = VK_PAD_DPAD_RIGHT,
		DPadDOWN = VK_PAD_DPAD_DOWN,
		Start = VK_PAD_START,
		Select = VK_PAD_BACK,
		LeftStick = VK_PAD_LTHUMB_PRESS,
		RightStick = VK_PAD_RTHUMB_PRESS,
		LeftShoulder = VK_PAD_LSHOULDER,
		RightShoulder = VK_PAD_RSHOULDER,
		LeftTrigger = VK_PAD_LTRIGGER,
		RightTrigger = VK_PAD_RTRIGGER,
	};

	class GameObject;
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		using CommandsMap = std::map<DWORD, Command*>;
		
		~InputManager();

		void InitDefaultInput(GameObject* controllerObject, GameObject* keyboardObject);
		bool ProcessInput();
		bool IsPressed(const ControllerButton& button) const;
		bool IsPressed(const SDL_Event& button) const;
		//void HandleInput(bool& bContinue, const GameObject& gameActor);
		bool HandleControllerInput();
		bool HandleKeyboardInput();
		Command* GetCommand(const ControllerButton& button);
		Command* GetCommand(const SDL_Keycode& button);

	private:
		XINPUT_STATE m_GamePadState{};
		XINPUT_KEYSTROKE m_Keystroke{};

		CommandsMap m_Commands{};
		//CommandsMap m_ControllerCommands{};
		//CommandsMap m_KeyboardCommands{};

		bool m_bRebindMode{ false };
		int m_errorCounter{ 0 };
	};

}
