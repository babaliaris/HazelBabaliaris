#include "hzpch.h"
#include "Renderer2D.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Hazel
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> FlatColorVertexArray;
		Ref<VertexArray> TextureVertexArray;
		Ref<Shader> FlatColorShader;
		Ref<Shader> TextureShader;
		ShaderLibrary ShaderLibrary;
	};

	static Renderer2DStorage *s_Data;






	void Renderer2D::Init()
	{
		//Initialize s_Data.
		s_Data = new Renderer2DStorage();


		//==============================Colored Quad==============================//

		//Quad Vertices.
		float colored_vertices[] =
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
		s_Data->FlatColorVertexArray = VertexArray::Create();
		vbo = VertexBuffer::Create(colored_vertices, sizeof(colored_vertices));
		ebo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));

		//Create the layout.
		BufferLayout colored_layout =
		{
			{ShaderDataType::FLOAT3, "position"}
		};


		//Add the layout to the VBO buffer.
		vbo->SetLayout(colored_layout);

		//Add VBO and EBO to the VAO.
		s_Data->FlatColorVertexArray->AddVertexBuffer(vbo);
		s_Data->FlatColorVertexArray->SetIndexBuffer(ebo);

		//Load the shader.
		s_Data->FlatColorShader = s_Data->ShaderLibrary.Load("src/Hazel/Renderer/Shaders/Color.vert", "src/Hazel/Renderer/Shaders/Color.frag");

		//==============================Colored Quad==============================//



		//==============================Textured Quad==============================//

		//Quad Vertices.
		float textured_vertices[] =
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f  // top left 
		};


		//Create the buffers and vertex array.
		s_Data->TextureVertexArray = Hazel::VertexArray::Create();
		vbo = Hazel::VertexBuffer::Create(textured_vertices, sizeof(textured_vertices));
		ebo = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));


		//Create the layout.
		Hazel::BufferLayout textured_layout =
		{
			{Hazel::ShaderDataType::FLOAT3, "position"},
			{Hazel::ShaderDataType::FLOAT2, "TexCoords"},
		};

		//Set the layout.
		vbo->SetLayout(textured_layout);


		//Add VBO and EBO to the VAO.
		s_Data->TextureVertexArray->AddVertexBuffer(vbo);
		s_Data->TextureVertexArray->SetIndexBuffer(ebo);

		//Load the shader.
		s_Data->TextureShader = s_Data->ShaderLibrary.Load("src/Hazel/Renderer/Shaders/Texture2D.vert", "src/Hazel/Renderer/Shaders/Texture2D.frag");
		//==============================Textured Quad==============================//
	}



	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}



	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->FlatColorShader->SetUniform("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
		s_Data->TextureShader->SetUniform("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
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

		//Set the transform matrix.
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
		transform			= glm::scale(transform, {size.x, size.y, 1.0f});
		s_Data->FlatColorShader->SetUniform("u_Transform", transform);

		//Set the color.
		s_Data->FlatColorShader->SetUniform("u_Color", color);

		//Bind the shader and the VAO.
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorVertexArray->Bind();

		//Draw Call.
		RenderCommand::DrawIndexed(s_Data->FlatColorVertexArray);

		//Unbind the shader and the VAO.
		s_Data->FlatColorVertexArray->Unbind();
		s_Data->FlatColorShader->Unbind();
	}




	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture);
	}



	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		//Set the transform matrix.
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
		transform = glm::scale(transform, { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetUniform("u_Transform", transform);

		//Set the color.
		s_Data->TextureShader->SetUniform("u_Diffuse", 0);

		//Bind the shader, texture and the VAO.
		s_Data->TextureShader->Bind();
		s_Data->TextureVertexArray->Bind();
		texture->Bind();

		//Draw Call.
		RenderCommand::DrawIndexed(s_Data->TextureVertexArray);

		//Unbind the shader, texture and the VAO.
		s_Data->TextureVertexArray->Unbind();
		s_Data->TextureShader->Unbind();
		texture->Unbind();
	}
}