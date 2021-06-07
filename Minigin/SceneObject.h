#pragma once
namespace Idiot_Engine
{
	// No longer used
	class SceneObject
	{
	public:
		virtual void FixedUpdate(float deltaTime) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void LateUpdate(float deltaTime) = 0;
		virtual void Render(float nextFrameTime) const = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};

}
