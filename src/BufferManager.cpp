#include "../include/hgui/header/BufferManager.h"
#include "../include/hgui/header/Buffer.h"
#include "../include/hgui/header/TextureManager.h"
#include "../include/hgui/header/Image.h"

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Buffer> hgui::BufferManager::create(const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize)
{
	kernel::ImageData bufferData
			{
				.size = static_cast<kernel::Size<unsigned>>(bufferSize),
				.channel = channels::RGBA,
				.pixels = kernel::ImageData::pointer(nullptr, nullptr)
			};
	auto texture = TextureManager::create(std::make_shared<kernel::Image>(std::move(bufferData)));
	return std::make_shared<kernel::Buffer>(shader, texture);
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Buffer>> hgui::BufferManager::m_buffers;

const std::shared_ptr<hgui::kernel::Buffer>& hgui::BufferManager::create(const std::string& bufferID, const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize)
{
	if (!m_buffers.contains(bufferID))
	{
		kernel::ImageData bufferData
				{
					.size = static_cast<kernel::Size<unsigned>>(bufferSize),
					.channel = channels::RGBA,
					.pixels = kernel::ImageData::pointer(nullptr, [](unsigned char*)
						{
						})
				};
		auto& texture = TextureManager::create("HGUI_TEXTURE_FRAMEBUFFER_" + bufferID,
			std::make_shared<kernel::Image>(std::move(bufferData)));
		m_buffers[bufferID] = std::make_shared<kernel::Buffer>(shader, texture);
		return m_buffers[bufferID];
	}
	throw std::runtime_error(("THERE IS ALREADY A BUFFER WITH THE ID : " + bufferID).c_str());
}

const std::shared_ptr<hgui::kernel::Buffer>& hgui::BufferManager::get(const std::string& bufferID)
{
	if (m_buffers.contains(bufferID))
	{
		return m_buffers[bufferID];
	}
	throw std::runtime_error(("THERE IS NO BUFFER WITH THE ID : " + bufferID).c_str());
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
