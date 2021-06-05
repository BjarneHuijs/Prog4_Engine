#include "MiniginPCH.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Command.h"

using namespace Idiot_Engine;
bool InputManager::ProcessInput()
{
	// Controller handling
	ZeroMemory(&m_GamePadState, sizeof(XINPUT_STATE));
	// Simply get the state of the controller from XInput.
	const DWORD dwResult = XInputGetState(0, &m_GamePadState);
	if (dwResult != ERROR_SUCCESS)
	{
		// Controller is not connected
		std::cout << "Controller is not connected" << std::endl;
	}
	else 
	{
		const auto result = XInputGetKeystroke(0, 0, &m_Keystroke);

	}

	const bool controllerResult = HandleControllerInput();
    if (!controllerResult) return controllerResult;
	
	// Keyboard handling
    const bool keyboardResult = HandleKeyboardInput();
    if (!keyboardResult) return keyboardResult;

	return true;
}

bool InputManager::IsPressed(const ControllerButton& button) const
{
	if (m_Keystroke.VirtualKey == button && m_Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
		return true;

	return false;
}

bool InputManager::IsPressed(const SDL_Event& button) const
{
    if (button.type == SDL_KEYDOWN)
        return true;

    return false;
}

bool InputManager::HandleControllerInput()
{
    if (IsPressed(ControllerButton::LeftTrigger))
    {
        m_bRebindMode = true;
    }
    else if (IsPressed(ControllerButton::Select))
    {
        return false;
    }

#pragma region swapBindings
    bool oldKeyDefined{ false };
    bool newKeyDefined{ false };

    XINPUT_KEYSTROKE oldKey{};

    XINPUT_KEYSTROKE newKey{};

    while (m_bRebindMode)
    {
        if (!oldKeyDefined)
        {

            XInputGetKeystroke(0, 0, &oldKey);
            if (oldKey.Flags == XINPUT_KEYSTROKE_KEYDOWN && oldKey.VirtualKey != ControllerButton::LeftTrigger && oldKey.VirtualKey != ControllerButton::Select)
            {
                oldKeyDefined = true;
                std::cout << "old key selected" << std::endl;

            }
        }
        else if (oldKeyDefined && !newKeyDefined)
        {
            XInputGetKeystroke(0, 0, &newKey);
            if (newKey.Flags == XINPUT_KEYSTROKE_KEYDOWN && newKey.VirtualKey != ControllerButton::LeftTrigger && newKey.VirtualKey != ControllerButton::Select)
            {
                newKeyDefined = true;
                std::cout << "new key selected" << std::endl;

            }
        }
        else if (oldKeyDefined && newKeyDefined)
        {
            ControllerButton oldButton{ static_cast<ControllerButton>(oldKey.VirtualKey) };
            ControllerButton newButton{ static_cast<ControllerButton>(newKey.VirtualKey) };
            //auto command = m_ControllerCommands.extract(oldButton);
            //auto otherCommand = m_ControllerCommands.extract(newButton);
            auto command = m_Commands.extract(oldButton);
            auto otherCommand = m_Commands.extract(newButton);
            if (command.empty())
            {
                std::cout << "Cannot rebind non-existing command" << std::endl;
                m_bRebindMode = false;
            }
            else
            {
                if (!otherCommand.empty())
                {
                    otherCommand.key() = command.key();
                    //m_ControllerCommands.insert(std::move(otherCommand));
                    m_Commands.insert(std::move(otherCommand));

                }

                oldButton = { static_cast<ControllerButton>(newKey.VirtualKey) };
                command.key() = oldButton;

                //m_ControllerCommands.insert(std::move(command));
                m_Commands.insert(std::move(command));

                m_bRebindMode = false;

                std::cout << "Rebound keys" << std::endl;
            }
        }

    }
#pragma endregion
	
    const ControllerButton button{ static_cast<ControllerButton>(m_Keystroke.VirtualKey) };
    if (IsPressed(button))
    {
        const auto command = GetCommand(button);
        if (command == nullptr)
        {
            std::cout << "Controller nullptr command" << std::endl;
            m_Keystroke = XINPUT_KEYSTROKE{};

            return true;
        }

        command->Execute();
        m_Keystroke = XINPUT_KEYSTROKE{};
    }
	
    return true;
}

bool InputManager::HandleKeyboardInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
        if (IsPressed(e))
        {
			//if (e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }
           
            const auto command = GetCommand(e.key.keysym.sym);
            if (command == nullptr)
            {
                std::cout << "Keyboard nullptr command" << std::endl;
                m_Keystroke = XINPUT_KEYSTROKE{};

                return true;
            }

            command->Execute();
            m_Keystroke = XINPUT_KEYSTROKE{};
            

        }
        
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            //return false;

        }
    }
    return true;
}

Command* InputManager::GetCommand(const ControllerButton& button)
{
	auto& command = m_Commands[button];
	if (command) return command;

	return nullptr;
}

Command* InputManager::GetCommand(const SDL_Keycode& button)
{
    auto& command = m_Commands[button];
    if (command) return command;

    return nullptr;
}



InputManager::~InputManager()
{
    for (std::pair<DWORD, Command*> pair : m_Commands)
    {
        delete pair.second;
        pair.second = nullptr;
    }
}

void InputManager::AddCommand(DWORD inputValue, Command* command)
{
	m_Commands.insert(std::make_pair(inputValue, command));
	//switch (inputEvent)
	//{
	//case EventTypes::MoveTopLeft: 
 //       m_Commands.insert(std::make_pair(ControllerButton::DPadUp, new MoveTopLeft(target)));
 //       m_Commands.insert(std::make_pair(SDLK_w, new MoveTopLeft(target)));
 //       break;
	//case EventTypes::MoveTopRight: 
 //       m_Commands.insert(std::make_pair(ControllerButton::DPadRight, new MoveTopRight(target)));
 //       m_Commands.insert(std::make_pair(SDLK_d, new MoveTopRight(target)));
 //       break;
	//case EventTypes::MoveBotLeft: 
 //       m_Commands.insert(std::make_pair(ControllerButton::DPadLeft, new MoveBotLeft(target)));
 //       m_Commands.insert(std::make_pair(SDLK_a, new MoveBotLeft(target)));
 //       break;
	//case EventTypes::MoveBotRight: 
 //       m_Commands.insert(std::make_pair(ControllerButton::DPadDOWN, new MoveBotRight(target)));
 //       m_Commands.insert(std::make_pair(SDLK_s, new MoveBotRight(target)));
 //       break;
	//default: 
 //       break;
	//}
}

//void InputManager::InitDemoInput(GameObject* controllerObject, GameObject* keyboardObject)
//{
//    // Init default controller commands
//	m_Commands.insert(std::make_pair(ControllerButton::ButtonA, new KillCoily(controllerObject)));
//	m_Commands.insert(std::make_pair(ControllerButton::ButtonX, new ChangeColor(controllerObject)));
//	m_Commands.insert(std::make_pair(ControllerButton::ButtonB, new CatchNPC(controllerObject)));
//	m_Commands.insert(std::make_pair(ControllerButton::ButtonY, new Kill(controllerObject)));
//	m_Commands.insert(std::make_pair(ControllerButton::RightShoulder, new CalculateRemainingDiscs(controllerObject)));
//	//m_ControllerCommands.insert(std::make_pair(ControllerButton::ButtonB, std::make_unique<Fire>(Fire())));
//	//m_ControllerCommands.insert(std::make_pair(ControllerButton::ButtonX, std::make_unique<Duck>(Duck())));
//	//m_ControllerCommands.insert(std::make_pair(ControllerButton::ButtonY, std::make_unique<Fart>(Fart())));
//
//	// Init default keyboard commands
//	//m_KeyboardCommands.insert(std::make_pair('E', std::make_unique<Kill>(Kill(controllerObject))));
//	m_Commands.insert(std::make_pair(SDLK_1, new KillCoily(keyboardObject)));
//	m_Commands.insert(std::make_pair(SDLK_2, new ChangeColor(keyboardObject)));
//	m_Commands.insert(std::make_pair(SDLK_3, new CatchNPC(keyboardObject)));
//	m_Commands.insert(std::make_pair(SDLK_4, new CalculateRemainingDiscs(keyboardObject)));
//	m_Commands.insert(std::make_pair(SDLK_e, new Kill(keyboardObject)));
//}
