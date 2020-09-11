#include <Hazel.h>
#include "imgui/imgui.h"

#include "Hazel/Renderer/Buffer.h"
#include "Platform/OpenGL/Shader.h"
#include <glad/glad.h>

namespace Hazel
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{

		case Hazel::ShaderDataType::FLOAT:	return GL_FLOAT;
		case Hazel::ShaderDataType::FLOAT2: return GL_FLOAT;
		case Hazel::ShaderDataType::FLOAT3: return GL_FLOAT;
		case Hazel::ShaderDataType::FLOAT4: return GL_FLOAT;
		case Hazel::ShaderDataType::MAT3:	return GL_FLOAT;
		case Hazel::ShaderDataType::MAT4:	return GL_FLOAT;
		case Hazel::ShaderDataType::INT:	return GL_INT;
		case Hazel::ShaderDataType::INT2:	return GL_INT;
		case Hazel::ShaderDataType::INT3:	return GL_INT;
		case Hazel::ShaderDataType::INT4:	return GL_INT;
		case Hazel::ShaderDataType::BOOL:	return GL_BOOL;

		}

		HZ_CORE_ASSERT(false, "Uknown ShaderDataType");
		return 0;
	}
};

class MyLayer : public Hazel::Layer
{
public:
	MyLayer(){}

	~MyLayer(){}


	void OnAttach() override
	{
		float vertices[] =
		{
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f, //Upper.
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f, //Bottom Left.
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f  //Bottom Right.
		};

		unsigned int indices[] =
		{
			0, 1, 2
		};


		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		m_vbo = Hazel::VertexBuffer::Create( vertices, sizeof(vertices) );
		m_ebo = Hazel::IndexBuffer::Create( indices, sizeof(indices) / sizeof(unsigned int) );

		{
			Hazel::BufferLayout layout =
			{
				{Hazel::ShaderDataType::FLOAT3, "position"},
				{Hazel::ShaderDataType::FLOAT4, "color"}
			};

			m_vbo->SetLayout(layout);
		}

		const Hazel::BufferLayout& layout = m_vbo->GetLayout();
		int index = 0;
		for ( const Hazel::BufferElement &element : m_vbo->GetLayout() )
		{
			glVertexAttribPointer(index, element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), element.Normilized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), (const void *)element.Offset);

			glEnableVertexAttribArray(index);
			index++;
		}

		m_shader = new Hazel::Shader("src/Hazel/Renderer/Shaders/Vertex.vert", "src/Hazel/Renderer/Shaders/Fragment.frag");
	}

	void OnUpdate() override 
	{
		glBindVertexArray(m_vao);
		m_shader->Use();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Hazel::Event &e)
	{
	}

private:
	Hazel::VertexBuffer* m_vbo;
	Hazel::IndexBuffer* m_ebo;
	Hazel::Shader* m_shader;
	unsigned int m_vao;
};


class MyApp : public Hazel::Application
{
public:

	MyApp()
	{
		PushLayer(new MyLayer());
	}

	~MyApp(){}
};

Hazel::Application *Hazel::createApp()
{
	return new MyApp();
}