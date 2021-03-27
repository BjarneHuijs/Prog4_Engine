#pragma once
namespace Idiot_Engine
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual void FixedUpdate(const float deltaTime) = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void LateUpdate(const float deltaTime) = 0;
		virtual void Render(const float nextFrame) const = 0;

		virtual void SetParent(GameObject* pParent);

		explicit BaseComponent(const std::string& name);
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		std::string GetName() const;
	protected:
		GameObject* m_pParent { nullptr };
		std::string m_Name{};
	};
}
