#pragma once
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{

	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;

	};



	class OpenGLIndexBuffer : public IndexBuffer
	{

	public:
		OpenGLIndexBuffer(unsigned int* vertices, unsigned int size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual unsigned int GetCount() const override;

	private:
		unsigned int m_RendererID, m_Count;

	};
}