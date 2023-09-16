#include <hgui/header/FontManager.h>

std::shared_ptr<hgui::kernel::Font> hgui::FontManager::create(const std::string& fontPath)
{
	return std::make_shared<kernel::Font>(fontPath);
}