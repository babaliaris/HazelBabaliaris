#include "hzpch.h"
#include "OpenGLVertexArray.h"
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











	OpenGLVertexArray::OpenGLVertexArray()
		: m_RenderedID(0)
	{
		glGenVertexArrays(1, &m_RenderedID);
	}




	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderedID);
	}




	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderedID);
	}




	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}




	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() != 0, "The layout has not been set!");

		glBindVertexArray(m_RenderedID);
		vertexBuffer->Bind();

		int index = 0;
		const BufferLayout& layout = vertexBuffer->GetLayout();

		for (const Hazel::BufferElement& element : layout)
		{
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type), element.Normilized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);

			glEnableVertexAttribArray(index);
			index++;
		}

		this->m_VertexBuffers.push_back(vertexBuffer);

		glBindVertexArray(0);
		vertexBuffer->Unbind();
	}




	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RenderedID);
		indexBuffer->Bind();

		this->m_IndexBuffer = indexBuffer;

		glBindVertexArray(0);
		indexBuffer->Unbind();
	}




	const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}




	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

}