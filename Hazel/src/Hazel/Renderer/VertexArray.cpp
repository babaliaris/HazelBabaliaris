#include "hzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	Ref<VertexArray> VertexArray::Create()
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
				return Ref<VertexArray>(std::make_shared <OpenGLVertexArray>());
			}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}
}