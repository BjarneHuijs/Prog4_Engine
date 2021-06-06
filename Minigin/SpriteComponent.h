#pragma once
#include <SDL_rect.h>
#include "BaseComponent.h"
#include <glm/detail/type_vec2.hpp>

// CAN ONLY HANDLE SINGLE LINE SPRITES CURRENTLY

namespace Idiot_Engine
{
	class Texture2D;
	class SpriteComponent : public BaseComponent
	{
	public:
		explicit SpriteComponent(const std::string& name, int nrOfFrames = 1);

		void FixedUpdate(const float) override {}; //deltaTime
		void Update(const float) override {}; //deltaTime
		void LateUpdate(const float) override {}; //deltaTime
		void Render(const float nextFrame) const override;

		void SetTexture(const std::string& filename);
		void SetScale(float xScale, float yScale);
		void ToNextFrame();
		void ToTargetFrame(int frameIndex);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		SDL_Rect m_Source, m_Destination;
		glm::vec2 m_Scale;
		int m_NrOfFrames;
	};
}