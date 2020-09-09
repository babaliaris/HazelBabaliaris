#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
	static bool s_GLFWInitialized = false;


	static void GLFWErrorCallback(int err, const char *desc)
	{
		HZ_CORE_ERROR("GLFW Error ({0}) : {1}", err, desc);
	}

	Window *Window::Create(const WindowProps &props)
	{
		return new WindowsWindow(props);
	}
}

Hazel::WindowsWindow::WindowsWindow(const WindowProps& props)
{
	Init(props);
}

Hazel::WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

void Hazel::WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	m_context->SwapBuffers();
}

void Hazel::WindowsWindow::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);

	else
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

bool Hazel::WindowsWindow::IsVSync() const
{
	return m_Data.VSync;
}

void Hazel::WindowsWindow::Init(const WindowProps& props)
{
	m_Data.Title  = props.Title;
	m_Data.Width  = props.Width;
	m_Data.Height = props.Height;

	HZ_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

	if (!s_GLFWInitialized)
	{
		int success = glfwInit();
		HZ_CORE_ASSERT(success, "Could not Initialize GLFW...");
		glfwSetErrorCallback(GLFWErrorCallback);

		s_GLFWInitialized = true;
	}

	m_Window	= glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
	m_context	= new OpenGLContext(m_Window);
	m_context->Init();

	

	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);


	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int x, int y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width  = x;
			data.Height = y;

			WindowResizeEvent e(x, y);

			data.EventCallback(e);
		});


	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;

			data.EventCallback(e);
		});


	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{

			case GLFW_PRESS:
			{
				KeyPressedEvent e(key, 0);
				data.EventCallback(e);
				break;
			}

			case GLFW_RELEASE:
			{
				KeyReleasedEvent e(key);
				data.EventCallback(e);
				break;
			}

			case GLFW_REPEAT:
			{
				KeyPressedEvent e(key, 1);
				data.EventCallback(e);
				break;
			}

			default:
				break;
			}
		});




	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent e(keycode);

			data.EventCallback(e);
		});


	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{

			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e(button);
				data.EventCallback(e);
				break;
			}

			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e(button);
				data.EventCallback(e);
				break;
			}

			default:
				break;
			}

		});


	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)x, (float)y);

			data.EventCallback(e);
		});


	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e((float)x, (float)y);

			data.EventCallback(e);
		});


	glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int x, int y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowMovedEvent e;

			data.EventCallback(e);
		});
}

void Hazel::WindowsWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
}
