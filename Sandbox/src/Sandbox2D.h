#pragma once
#include "Hazel.h"

class Sandbox2D : public Hazel::Layer
{
public:

	Sandbox2D()
		: m_CameraController((float)Hazel::Application::Get().GetWindow().GetWidth() / Hazel::Application::Get().GetWindow().GetHeight(), true)
	{
	}

	void OnAttach() override
	{
	}


	void OnDetach() override
	{
	}


	void OnUpdate(Hazel::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);



		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);

		Hazel::Renderer2D::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", &m_SquareColor[0]);
		ImGui::End();
	}

	void OnEvent(Hazel::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Hazel::OrthographicCameraController m_CameraController;

	Hazel::Ref <Hazel::Shader> m_shader;

	glm::vec4 m_SquareColor = glm::vec4(0.77f, 0.89f, 0.21f, 1.0F);

	Hazel::Ref <Hazel::VertexArray> m_vao;

	Hazel::ShaderLibrary shader_lib;

};