#pragma once
#include "RendererAPI.h"

namespace Hazel
{
	class RenderCommand
	{

	public:

		static void Init();

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}


		inline static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

	private:
		static RendererAPI* s_RendererAPI;


	};
}