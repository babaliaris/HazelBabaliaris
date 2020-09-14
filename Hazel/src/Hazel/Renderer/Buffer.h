#pragma once
#include <iostream>
#include <vector>

namespace Hazel
{

	enum class ShaderDataType
	{
		None=0,
		FLOAT, FLOAT2, FLOAT3, FLOAT4,
		MAT3, MAT4,
		INT, INT2, INT3, INT4,
		BOOL
	};


	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{

		case Hazel::ShaderDataType::FLOAT:
			return 4;

		case Hazel::ShaderDataType::FLOAT2:
			return 4 * 2;

		case Hazel::ShaderDataType::FLOAT3:
			return 4 * 3;

		case Hazel::ShaderDataType::FLOAT4:
			return 4 * 4;

		case Hazel::ShaderDataType::MAT3:
			return 4 * 3 * 3;

		case Hazel::ShaderDataType::MAT4:
			return 4 * 4 * 4;

		case Hazel::ShaderDataType::INT:
			return 4;

		case Hazel::ShaderDataType::INT2:
			return 4 * 2;

		case Hazel::ShaderDataType::INT3:
			return 4 * 3;

		case Hazel::ShaderDataType::INT4:
			return 4 * 4;

		case Hazel::ShaderDataType::BOOL:
			return 1;
		}

		HZ_CORE_ASSERT(false, "Uknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType	Type;
		std::string		Name;
		unsigned int	Size;
		unsigned int	Offset;
		bool			Normilized;

		BufferElement()
			: Type(ShaderDataType::None), Name(""), Size(0), Offset(0), Normilized(false)
		{}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized=false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normilized(normalized)
		{}

		unsigned int GetComponentCount() const
		{
			switch (Type)
			{

			case Hazel::ShaderDataType::FLOAT:
				return 1;

			case Hazel::ShaderDataType::FLOAT2:
				return 2;

			case Hazel::ShaderDataType::FLOAT3:
				return 3;

			case Hazel::ShaderDataType::FLOAT4:
				return 4;

			case Hazel::ShaderDataType::MAT3:
				return 3 * 3;

			case Hazel::ShaderDataType::MAT4:
				return 4 * 4;

			case Hazel::ShaderDataType::INT:
				return 1;

			case Hazel::ShaderDataType::INT2:
				return 2;

			case Hazel::ShaderDataType::INT3:
				return 3;

			case Hazel::ShaderDataType::INT4:
				return 4;

			case Hazel::ShaderDataType::BOOL:
				return 1;

			}

			return 0;
		}
	};

	class BufferLayout
	{

	public:

		BufferLayout(){}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }


	private:
		void CalculateOffsetAndStride()
		{
			unsigned int offset = 0;
			m_Stride = 0;
			for (BufferElement &element : m_Elements)
			{
				element.Offset	 = offset;

				offset			+= element.Size;
				m_Stride		+= element.Size;
			}
		}


	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;

	};


	class VertexBuffer
	{

	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout)  = 0;

		static Ref<VertexBuffer> Create(float* vertices, unsigned int size);
	};

	class IndexBuffer
	{

	public:
		virtual ~IndexBuffer() {}

		virtual void Bind()				const = 0;
		virtual void Unbind()			const = 0;
		virtual unsigned int GetCount() const = 0;

		static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int count);
	};
}