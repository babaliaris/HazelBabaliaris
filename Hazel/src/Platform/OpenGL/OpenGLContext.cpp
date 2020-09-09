#include "hzpch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_windowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "windowHandle shouldn't be null...");
	}




	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize GLAD...");
		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("\tOpenGL Vendor	: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("\tOpenGL Renderer	: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("\tOpenGL Version	: {0}", glGetString(GL_VERSION));
	}




	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}