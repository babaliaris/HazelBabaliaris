#include "hzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
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
				return dynamic_cast<VertexArray*>(new OpenGLVertexArray());
			}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}
}