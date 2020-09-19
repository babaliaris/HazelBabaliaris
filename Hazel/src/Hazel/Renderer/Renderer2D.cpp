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
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		ShaderLibrary ShaderLibrary;
	};

	static Renderer2DStorage *s_Data;






	void Renderer2D::Init()
	{
		//Initialize s_Data.
		s_Data = new Renderer2DStorage();

		//Quad Vertices.
		float textured_vertices[] =
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f  // top left 
		};

		//Quad Incices.
		unsigned int indices[] =
		{
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};


		//Buffers.
		Ref<VertexBuffer> vbo;
		Ref<IndexBuffer> ebo;

		//Create the buffers and vertex array.
		s_Data->QuadVertexArray = Hazel::VertexArray::Create();
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
		s_Data->QuadVertexArray->AddVertexBuffer(vbo);
		s_Data->QuadVertexArray->SetIndexBuffer(ebo);

		//Load the shader.
		s_Data->TextureShader = s_Data->ShaderLibrary.Load("src/Hazel/Renderer/Shaders/Texture2D.vert", "src/Hazel/Renderer/Shaders/Texture2D.frag");

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		unsigned int whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(unsigned int));
	}



	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}



	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
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
		s_Data->TextureShader->SetUniform("u_Transform", transform);

		//Set the color.
		s_Data->TextureShader->SetUniform("u_Color", color);
		s_Data->TextureShader->SetUniform("u_Diffuse", 0);
		s_Data->TextureShader->SetUniform("u_TilingFactor", 1.0f);

		//Bind the shader and the VAO.
		s_Data->TextureShader->Bind();
		s_Data->QuadVertexArray->Bind();
		s_Data->WhiteTexture->Bind();

		//Draw Call.
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

		//Unbind the shader and the VAO.
		s_Data->QuadVertexArray->Unbind();
		s_Data->TextureShader->Unbind();
		s_Data->WhiteTexture->Unbind();
	}




	void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		DrawQuad({ pos.x, pos.y, 0.0f }, size, texture, tiling, tintColor);
	}



	void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		//Set the transform matrix.
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
		transform			= glm::scale(transform, { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetUniform("u_Transform", transform);

		
		s_Data->TextureShader->SetUniform("u_Diffuse", 0);
		s_Data->TextureShader->SetUniform("u_Color", tintColor);
		s_Data->TextureShader->SetUniform("u_TilingFactor", tiling);

		//Bind the shader, texture and the VAO.
		s_Data->TextureShader->Bind();
		s_Data->QuadVertexArray->Bind();
		texture->Bind();

		//Draw Call.
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

		//Unbind the shader, texture and the VAO.
		s_Data->QuadVertexArray->Unbind();
		s_Data->TextureShader->Unbind();
		texture->Unbind();
	}



	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ pos.x, pos.y, 0.0f }, size, rotation, color);
	}



	void Renderer2D::DrawRotatedQuad(const glm::vec2& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ pos.x, pos.y, 0.0f }, size, rotation, texture, tiling, tintColor);
	}



	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		//Set the transform matrix.
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
		transform			= glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		transform			= glm::scale(transform, { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetUniform("u_Transform", transform);

		//Set the color.
		s_Data->TextureShader->SetUniform("u_Color", color);
		s_Data->TextureShader->SetUniform("u_Diffuse", 0);
		s_Data->TextureShader->SetUniform("u_TilingFactor", 1.0f);

		//Bind the shader and the VAO.
		s_Data->TextureShader->Bind();
		s_Data->QuadVertexArray->Bind();
		s_Data->WhiteTexture->Bind();

		//Draw Call.
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

		//Unbind the shader and the VAO.
		s_Data->QuadVertexArray->Unbind();
		s_Data->TextureShader->Unbind();
		s_Data->WhiteTexture->Unbind();
	}



	void Renderer2D::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tiling, const glm::vec4& tintColor)
	{
		//Set the transform matrix.
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
		transform			= glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		transform			= glm::scale(transform, { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetUniform("u_Transform", transform);


		s_Data->TextureShader->SetUniform("u_Diffuse", 0);
		s_Data->TextureShader->SetUniform("u_Color", tintColor);
		s_Data->TextureShader->SetUniform("u_TilingFactor", tiling);

		//Bind the shader, texture and the VAO.
		s_Data->TextureShader->Bind();
		s_Data->QuadVertexArray->Bind();
		texture->Bind();

		//Draw Call.
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

		//Unbind the shader, texture and the VAO.
		s_Data->QuadVertexArray->Unbind();
		s_Data->TextureShader->Unbind();
		texture->Unbind();
	}
}