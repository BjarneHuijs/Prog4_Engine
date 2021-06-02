#pragma once

struct SDL_Window;
namespace Idiot_Engine
{
	class GameObject;
	class TextObject;
	class Minigin
	{
	public:
		virtual ~Minigin() = default;

		virtual void Initialize();
		virtual void LoadGame();
		virtual void Cleanup();
		virtual void Run();
	protected:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		//SDL_Window* m_Window{};

	private:
		std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_1{};
		std::shared_ptr<Idiot_Engine::GameObject> m_pQBert_2{};
	};
}