#include "../include/hgui/header/FontManager.h"
#include "../include/hgui/header/Font.h"

std::shared_ptr<hgui::kernel::Font> hgui::FontManager::create(const std::string& fontPath)
{
	return std::make_shared<kernel::Font>(fontPath);
}
