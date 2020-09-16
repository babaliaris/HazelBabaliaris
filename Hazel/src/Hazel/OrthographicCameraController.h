#pragma once
#include "Renderer/OrthographicCamera.h"
#include "Core/Timestep.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	class OrthographicCameraController
	{

	public:
		OrthographicCameraController(float aspectRation, bool rotation = false);

		inline OrthographicCamera& GetCamera() { return m_Camera; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline void SetMoveSpeed(float value) { m_CameraTranslationSpeed = value; }
		inline void SetRotSpeed(float value) { m_CameraRotationSpeed = value; }
		inline void SetZoomSensitivity(float value) { m_ZoomSensitivity = value; }
		inline void SetMaxZoom(float value) { m_MaximumZoom = value; }


	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);


	private:
		float m_AspectRation;
		bool  m_Rotation;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition	= { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation		= 0;

		float m_CameraTranslationSpeed	= 3.0f;
		float m_CameraRotationSpeed		= 25.0f;
		float m_ZoomSensitivity			= 0.05f;
		float m_MaximumZoom				= 0.25f;

	};
}