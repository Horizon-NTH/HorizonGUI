#include <hgui/header/BufferManager.h>

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
