#include "hzpch.h"
#include "RenderComman.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}