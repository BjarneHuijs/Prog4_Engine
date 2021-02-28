#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <map>
namespace dae
{
	class Texture2D;
	class BaseComponent;
	class GameObject final : public SceneObject, public std::enable_shared_from_this<GameObject>
	{
	public:
		void FixedUpdate(const float deltaTime) override;
		void Update(const float deltaTime) override;
		void LateUpdate(const float deltaTime) override;
		void Render(const float nextFrameTime) const override;

		void SetTexture(const std::string& filename);
		void SetPosition(const float x, const float y);
		const Transform& GetPosition() const;

		void AddComponent(std::shared_ptr<BaseComponent> component, const std::string componentName);
		void RemoveComponent(const std::string componentName);
		template<typename T>
		std::shared_ptr<T> GetComponent() const;

		
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

	// templated function was provided by Martijn
	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponent() const
	{
		for(const auto& pair: m_pComponents)
		{
			if (typeid(*pair.second) == typeid(T))
			{
				//std::shared_ptr<BaseComponent> pComponent = pair.second;
				return std::static_pointer_cast<T>(pair.second);
			}
			/*if (pComponentCast)
				return pComponent;*/
		}
		return nullptr;
	}
}
