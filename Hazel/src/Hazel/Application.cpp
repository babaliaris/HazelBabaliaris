#include "hzpch.h"
#include "Application.h"
#include "glad/glad.h"
#include "Input.h"


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

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlayer(m_ImGuiLayer);
}



Hazel::Application::~Application()
{
}



void Hazel::Application::run()
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (m_Running)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();
		

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
