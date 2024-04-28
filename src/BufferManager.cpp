#include "../include/hgui/header/BufferManager.h"
#include "../include/hgui/header/Buffer.h"
#include "../include/hgui/header/TextureManager.h"
#include "../include/hgui/header/Image.h"

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
