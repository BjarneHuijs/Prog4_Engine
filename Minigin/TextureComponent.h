#pragma once
#include <SDL_rect.h>
#include "BaseComponent.h"

namespace Idiot_Engine
{
	class Texture2D;
	class TextureComponent : public BaseComponent
	{
	public:
		explicit TextureComponent(const std::string& name);

		void FixedUpdate(const float) override{}; //deltaTime
		void Update(const float) override{}; //deltaTime
		void LateUpdate(const float) override{}; //deltaTime
		void Render(const float nextFrame) const override;
		
		void SetTexture(const std::string& filename);
		void SetScale(float xScale, float yScale);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		SDL_Rect m_Source, m_Destination;
		glm::vec2 m_Scale;
	};
}
