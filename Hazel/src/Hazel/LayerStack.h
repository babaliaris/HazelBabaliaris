#pragma once
#include <vector>
#include "Core.h"
#include "Layer.h"


namespace Hazel
{

	class HAZEL_API LayerStack
	{

	public:
		LayerStack();
		virtual ~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlayer(Layer* overlayer);
		void PopLayer(Layer* layer);
		void PopOverlayer(Layer* overlayer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;

	};

}