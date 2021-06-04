#pragma once
#include <SDL_rect.h>

#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Idiot_Engine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(/*SDL_Window* window*/);
		void Render(const float nextFrameTime);// const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, SDL_Rect source, SDL_Rect destination) const;
		SDL_Window* GetWindow() const { return m_Window; }
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		bool m_ShowDemo{ true };

		void Player1Controls();
		void Player2Controls();
	};
}

