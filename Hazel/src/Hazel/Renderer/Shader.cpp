#include <hzpch.h>
#include "Shader.h"
#include "Hazel/Core.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"



namespace Hazel
{
	Ref<Shader> Shader::Create(const char* v_path, const char* f_path)
	{
		switch (Renderer::GetApi())
		{
			case RendererAPI::API::None:
			{
				HZ_CORE_ASSERT(false, "RendererAPI::None is not currently supported.");
				return nullptr;
			}

			case RendererAPI::API::OpenGL:
			{
				return Ref<Shader>(new OpenGLShader(v_path, f_path));
			}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}
}