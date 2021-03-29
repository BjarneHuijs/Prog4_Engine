#pragma once

struct SDL_Window;
namespace Idiot_Engine
{
	class GameObject;
	class TextObject;
	class Minigin
	{
	public:
		
		void Initialize();
		void LoadGame();
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		//SDL_Window* m_Window{};

		std::shared_ptr<GameObject> m_pQBert_1{};
		std::shared_ptr<GameObject> m_pQBert_2{};
	};
}