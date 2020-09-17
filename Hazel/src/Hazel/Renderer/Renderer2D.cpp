#include "hzpch.h"
#include "Renderer2D.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

//TODO:: TO BE ABSTRUCTED!!!
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
		ShaderLibrary ShaderLibrary;
	};

	static Renderer2DStorage *s_Data;






	void Renderer2D::Init()
	{
		//Initialize s_Data.
		s_Data = new Renderer2DStorage();

		//Quad Vertices.
		float vertices[] =
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		//Quad Incices.
		unsigned int indices[] =
		{
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		//Declare VBO and EBO.
		Ref<VertexBuffer> vbo;
		Ref<IndexBuffer>  ebo;

		//Create the buffers and vertex array.
		s_Data->QuadVertexArray = VertexArray::Create();
		vbo = VertexBuffer::Create(vertices, sizeof(vertices));
		ebo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

		//Create the layout.
		BufferLayout layout =
		{
			{ShaderDataType::FLOAT3, "position"}
		};


		//Add the layout to the VBO buffer.
		vbo->SetLayout(layout);

		//Add VBO and EBO to the VAO.
		s_Data->QuadVertexArray->AddVertexBuffer(vbo);
		s_Data->QuadVertexArray->SetIndexBuffer(ebo);

		//Load the shader.
		s_Data->FlatColorShader = s_Data->ShaderLibrary.Load("src/Hazel/Renderer/Shaders/Color.vert", "src/Hazel/Renderer/Shaders/Color.frag");
	}



	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}



	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->SetUniform("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->SetUniform("u_Transform", glm::mat4(1.0f));
	}



	void Renderer2D::EndScene()
	{
	}



	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
	}



	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		//Set the color.
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->SetUniform("u_Color", color);

		//Bind the shader and the VAO.
		s_Data->FlatColorShader->Bind();
		s_Data->QuadVertexArray->Bind();

		//Draw Call.
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

		//Unbind the shader and the VAO.
		s_Data->QuadVertexArray->Unbind();
		s_Data->FlatColorShader->Unbind();
	}
}