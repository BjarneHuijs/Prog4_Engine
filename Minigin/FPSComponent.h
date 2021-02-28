#pragma once
#include "TextComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class FPSComponent : public TextComponent
	{
	public:
		void FixedUpdate(const float deltaTime) override;
		void Update(const float deltaTime) override;
		void LateUpdate(const float deltaTime) override;
		//void Render(const float nextFrameTime) const override;
		
		
		explicit FPSComponent(const std::string& name, const std::string& text, const std::shared_ptr<Font>& font, const Color& color = { 255, 255, 255 });
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent & other) = delete;
		FPSComponent(FPSComponent && other) = delete;
		FPSComponent& operator=(const FPSComponent & other) = delete;
		FPSComponent& operator=(FPSComponent && other) = delete;
	};
}

