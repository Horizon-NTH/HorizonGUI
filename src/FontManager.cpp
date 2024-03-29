#include "../include/hgui/header/FontManager.h"
#include "../include/hgui/header/Font.h"

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Font> hgui::FontManager::create(const std::string& fontPath)
{
	return std::make_shared<kernel::Font>(fontPath);
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Font>> hgui::FontManager::m_fonts;

const std::shared_ptr<hgui::kernel::Font>& hgui::FontManager::create(const std::string& fontID, const std::string& fontPath)
{
	if (!m_fonts.contains(fontID))
	{
		m_fonts[fontID] = std::make_shared<kernel::Font>(fontPath);
		return m_fonts[fontID];
	}
	throw std::runtime_error(("THERE IS ALREADY A FONT WITH THE ID : " + fontID).c_str());
}

const std::shared_ptr<hgui::kernel::Font>& hgui::FontManager::get(const std::string& fontID)
{
	if (m_fonts.contains(fontID))
	{
		return m_fonts[fontID];
	}
	throw std::runtime_error(("THERE IS NO FONT WITH THE ID : " + fontID).c_str());
}

void hgui::FontManager::destroy(const std::initializer_list<std::string>& fontsID)
{
	if (fontsID.size())
	{
		for (const auto& id : fontsID)
		{
			m_fonts.erase(id);
		}
	}
	else
	{
		m_fonts.clear();
	}
}
#endif
