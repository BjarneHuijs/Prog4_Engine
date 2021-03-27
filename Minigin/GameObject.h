#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <map>

#include "BaseComponent.h"

namespace Idiot_Engine
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

		//void SetTexture(const std::string& filename);
		void SetPosition(const float x, const float y);
		const Transform& GetTransform() const;

		void AddComponent(std::shared_ptr<BaseComponent> component, const std::string componentName);
		void RemoveComponent(const std::string componentName);
		
		template<typename T>
		std::shared_ptr<T> GetComponentByType() const;
		template<typename T>
		std::shared_ptr<T> GetComponentByName(const std::string& name) const;

		
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		//std::shared_ptr<Texture2D> m_Texture{};
		std::map<std::string, std::shared_ptr<BaseComponent>> m_pComponents{};
	};

	// templated function was provided by Martijn
	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponentByType() const
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

	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponentByName(const std::string& name) const
	{
		for(const auto& pair: m_pComponents)
		{
			std::string compName{ pair.second->GetName() };
			
			if (typeid(*pair.second) == typeid(T) && compName._Equal(name))
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
