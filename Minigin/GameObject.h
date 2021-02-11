#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <map>
namespace dae
{
	class Texture2D;
	class BaseComponent;
	class GameObject final : public SceneObject
	{
	public:
		void FixedUpdate(const float deltaTime) override;
		void Update(const float deltaTime) override;
		void LateUpdate(const float deltaTime) override;
		void Render(const float nextFrameTime) const override;

		void SetTexture(const std::string& filename);
		void SetPosition(const float x, const float y);

		void AddComponent(std::shared_ptr<BaseComponent> component, const std::string componentName);
		void RemoveComponent(const std::string componentName);
		
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
		std::map<std::string, std::shared_ptr<BaseComponent>> m_pComponents{};
	};
}
