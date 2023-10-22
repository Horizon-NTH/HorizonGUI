#include <hgui/header/BufferManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Buffer> hgui::BufferManager::create(const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize)
{
	kernel::ImageData bufferData
	{
		.width = static_cast<int>(bufferSize.width),
		.height = static_cast<int>(bufferSize.height),
		.channel = channels::RGBA,
		.pixels = NULL
	};
	auto texture = TextureManager::create(std::make_shared<kernel::Image>("", bufferData));
	return std::make_shared<kernel::Buffer>(shader, texture);
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Buffer>> hgui::BufferManager::m_buffers;

const std::shared_ptr<hgui::kernel::Buffer>& hgui::BufferManager::create(const std::string& bufferID, const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize)
{
	if (m_buffers.find(bufferID) == m_buffers.end())
	{
		kernel::ImageData bufferData
		{
			.width = static_cast<int>(bufferSize.width),
				.height = static_cast<int>(bufferSize.height),
				.channel = channels::RGBA,
				.pixels = NULL
		};
		auto& texture = TextureManager::create("HGUI_TEXTURE_FRAMEBUFFER_" + bufferID,
			std::make_shared<kernel::Image>("", bufferData));
		m_buffers[bufferID] = std::make_shared<kernel::Buffer>(shader, texture);
		return m_buffers[bufferID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A BUFFER WITH THE ID : " + bufferID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Buffer>& hgui::BufferManager::get(const std::string& bufferID)
{
	if (m_buffers.find(bufferID) != m_buffers.end())
	{
		return m_buffers[bufferID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO BUFFER WITH THE ID : " + bufferID).c_str());
	}
}

void hgui::BufferManager::destroy(const std::initializer_list<std::string>& buffersID)
{
	if (buffersID.size())
	{
		for (const std::string& bufferID : buffersID)
		{
			m_buffers.erase(bufferID);
		}
	}
	else
	{
		m_buffers.clear();
	}
}
#endif
