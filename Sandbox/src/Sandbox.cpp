#include <Hazel.h>
#include "imgui/imgui.h"

class MyLayer : public Hazel::Layer
{
public:
	MyLayer(){}

	~MyLayer(){}

	void OnUpdate() override 
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_SPACE))
			HZ_INFO("SPACE IS PRESSED");

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::ColorEdit4("", new float[4]);
		ImGui::End();
	}

	void OnEvent(Hazel::Event &e)
	{
		if (e.IsInCategory(Hazel::EventCategory::EventCategoryKeyboard))
			HZ_INFO("WORKING!");
		else
			HZ_ERROR("WORKING wtf?");
	}
};


class MyApp : public Hazel::Application
{
public:

	MyApp()
	{
		PushLayer(new MyLayer());
	}

	~MyApp(){}
};

Hazel::Application *Hazel::createApp()
{
	return new MyApp();
}