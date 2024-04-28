#include "../include/hgui/header/TextureManager.h"
#include "../include/hgui/header/Texture.h"

std::shared_ptr<hgui::kernel::Texture> hgui::TextureManager::create(const std::shared_ptr<kernel::Image>& image)
{
	return std::make_shared<kernel::Texture>(image);
}
