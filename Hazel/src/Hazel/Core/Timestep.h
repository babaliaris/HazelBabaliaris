#pragma once
#include <glm/glm.hpp>

namespace Hazel
{
	class Timestep
	{

	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		inline float GetSeconds()
		{
			return m_Time;
		}

		inline float GetMilliseconds()
		{
			return m_Time * 1000.0f;
		}

		operator float() const { return m_Time; }

		//Overload * operator with a glm::vec3.
		glm::vec3 operator*(const glm::vec3& vector)
		{
			return vector * m_Time;
		}

	private:
		float m_Time;

	};
}