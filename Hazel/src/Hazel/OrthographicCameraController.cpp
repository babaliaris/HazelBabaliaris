#include "hzpch.h"
#include "OrthographicCameraController.h"
#include "Hazel/Input.h"
#include "Hazel/Keycodes.h"
#include "Hazel/Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	OrthographicCameraController::OrthographicCameraController(float aspectRation, bool rotation)
		: m_AspectRation(aspectRation), m_Rotation(rotation), 
			m_Camera(-aspectRation * m_ZoomLevel, aspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}



	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(HZ_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts * m_ZoomLevel;

		else if (Input::IsKeyPressed(HZ_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts * m_ZoomLevel;

		if (Input::IsKeyPressed(HZ_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts * m_ZoomLevel;

		else if (Input::IsKeyPressed(HZ_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts * m_ZoomLevel;


		if (m_Rotation)
		{
			if (Input::IsKeyPressed(HZ_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts * m_ZoomLevel;

			else if (Input::IsKeyPressed(HZ_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts * m_ZoomLevel;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}



	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}



	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * m_ZoomSensitivity;
		m_ZoomLevel  = std::max(m_ZoomLevel, m_MaximumZoom);

		m_Camera.SetProjection(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}



	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRation = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRation * m_ZoomLevel, m_AspectRation * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}