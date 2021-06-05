#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace Idiot_Engine
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		glm::vec2 GetPosition2D() const { return {m_Position.x, m_Position.y}; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
