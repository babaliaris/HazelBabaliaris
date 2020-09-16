#include "hzpch.h"
#include "LayerStack.h"

Hazel::LayerStack::LayerStack()
{
}





Hazel::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
		delete layer;
}





void Hazel::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
	m_LayerInsertIndex++;
}





void Hazel::LayerStack::PushOverlayer(Layer* overlayer)
{
	m_Layers.emplace_back(overlayer);
}





void Hazel::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
		m_LayerInsertIndex--;
	}
}





void Hazel::LayerStack::PopOverlayer(Layer* overlayer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);

	if (it != m_Layers.end())
		m_Layers.erase(it);
}
