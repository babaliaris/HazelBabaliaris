#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Hazel
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}



	void Renderer::EndScene()
	{
	}


	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}



	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{

		//Use the shader and upload the ViewProjection matrix.
		shader->Bind();
		shader->SetUniform("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
		shader->SetUniform("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		vertexArray->Unbind();
	}



	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}
}