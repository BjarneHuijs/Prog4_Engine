#pragma once
#include "TextComponent.h"
#include <chrono>

namespace dae
{
	class Font;
	class Texture2D;
	class FPSComponent : public TextComponent
	{
	public:
		//void FixedUpdate(const float deltaTime) override;
		//void Update(const float deltaTime) override;
		void LateUpdate(const float deltaTime) override;
		void Render(const float nextFrameTime) const override;
		
		
		explicit FPSComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent & other) = delete;
		FPSComponent(FPSComponent && other) = delete;
		FPSComponent& operator=(const FPSComponent & other) = delete;
		FPSComponent& operator=(FPSComponent && other) = delete;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
		int m_FPS;
		int m_NrOfFrames;
	};
}

