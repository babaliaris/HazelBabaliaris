#include "hzpch.h"
#include "WindowsInput.h"
#include "Hazel/Core/Application.h"
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>



namespace Hazel
{
	Input *Input::s_Instance = new WindowsInput();
}


bool Hazel::WindowsInput::IsKeyPressedImp(int keycode)
{
	GLFWwindow *window	= (GLFWwindow *)Application::Get().GetWindow().GetNativeWindow();
	int state			= glfwGetKey(window, keycode);

	return state == GLFW_PRESS || state == GLFW_REPEAT;
}




bool Hazel::WindowsInput::IsMouseButtonPressedImpl(int button)
{
	GLFWwindow* window	= (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
	int state			= glfwGetMouseButton(window, button);

	return state == GLFW_PRESS;
}




std::pair<float, float> Hazel::WindowsInput::GetMousePositionImpl()
{
	GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();

	double x, y;

	glfwGetCursorPos(window, &x, &y);

	return {(float)x, (float)y};
}




float Hazel::WindowsInput::GetMouseXImpl()
{
	auto [x, y] = this->GetMousePosition();
	return (float)x;
}




float Hazel::WindowsInput::GetMouseYImpl()
{
	auto [x, y] = this->GetMousePosition();
	return (float)y;
}
