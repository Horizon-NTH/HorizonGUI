#include <hgui/header/BufferManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Buffer>> hgui::BufferManager::m_buffers;

const std::shared_ptr<hgui::kernel::Buffer>& hgui::BufferManager::create(const std::string& bufferName, const std::shared_ptr<kernel::Shader>& shader)
{
	if (m_buffers.find(bufferName) == m_buffers.end())
	{
		kernel::ImageData bufferData; bufferData.width = static_cast<int>(MonitorManager::get_primary_monitor()->get_size().x); bufferData.height = static_cast<int>(MonitorManager::get_primary_monitor()->get_size().y); bufferData.pixels = NULL; bufferData.channel = kernel::RGBA;
		auto& texture = ResourceManager::load_texture("HGUI_TEXTURE_FRAMEBUFFER_" + bufferName, std::make_shared<kernel::Image>("", bufferData));
		m_buffers[bufferName] = std::make_shared<kernel::Buffer>(shader, texture);
		return m_buffers[bufferName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A BUFFER WITH THE NAME : " + bufferName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Buffer>& hgui::BufferManager::get(const std::string& bufferName)
{
	if (m_buffers.find(bufferName) != m_buffers.end())
	{
		return m_buffers[bufferName];
	}
	else
	{
		throw std::exception(("THERE IS NO BUFFER WITH THE NAME : " + bufferName).c_str());
	}
}

void hgui::BufferManager::delete_buffers(std::initializer_list<std::string> buffersNames)
{
	if (buffersNames.size())
	{
		for (const std::string& str : buffersNames)
		{
			m_buffers.erase(str);
		}
	}
	else
	{
		m_buffers.clear();
	}
}
