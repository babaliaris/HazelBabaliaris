#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

namespace Hazel
{
	class HAZEL_API Application
	{

	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* overlayer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }


	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer *m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		bool OnWindowCloseEvent(WindowCloseEvent& e);
	};
}
