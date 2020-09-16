#include "hzpch.h"
#include "Hazel/Core/Application.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Core/Timestep.h"

#include "GLFW/glfw3.h"


namespace Hazel
{
	Application* Application::s_Instance = nullptr;
}


Hazel::Application::Application()
{
	m_Window = std::unique_ptr<Window>(Window::Create());

	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	HZ_CORE_ASSERT(!s_Instance, "Application Already Exists...");
	s_Instance = this;

	Renderer::Init();

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlayer(m_ImGuiLayer);
}



Hazel::Application::~Application()
{
}



void Hazel::Application::run()
{

	RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

	while (m_Running)
	{
		float time			= (float)glfwGetTime();
		Timestep timestep	= time - m_LastFrameTime;
		m_LastFrameTime		= time;

		RenderCommand::Clear();

		if (!m_Minimized)
		{
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);
		}
		

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();


		m_Window->OnUpdate();
	}
}



void Hazel::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	//Dispatching WindowCloseEvent
	dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowCloseEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResizeEvent, this, std::placeholders::_1));

	//For all the layers, call the onEvent method.
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(e);

		if (e.m_Handled)
			break;
	}
}





void Hazel::Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}





void Hazel::Application::PushOverlayer(Layer* overlayer)
{
	m_LayerStack.PushOverlayer(overlayer);
	overlayer->OnAttach();
}




bool Hazel::Application::OnWindowCloseEvent(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}



bool Hazel::Application::OnWindowResizeEvent(WindowResizeEvent& e)
{

	//Window is minimized.
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}

	Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

	m_Minimized = false;

	return false;
}
