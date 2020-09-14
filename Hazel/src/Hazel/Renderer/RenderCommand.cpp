#include "hzpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();



	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}
}