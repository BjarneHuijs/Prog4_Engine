#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual void FixedUpdate(const float deltaTime) = 0;
		virtual void Update(const float deltaTime) = 0;
		virtual void LateUpdate(const float deltaTime) = 0;
		virtual void Render(const float nextFrame) const = 0;

		virtual void SetParent(GameObject* parent);
		
		BaseComponent() = default;
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		GameObject* m_pParent { nullptr };
	};
}
