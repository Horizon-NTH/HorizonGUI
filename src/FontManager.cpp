#include <hgui/header/FontManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Font>> hgui::FontManager::m_fonts;

const std::shared_ptr<hgui::kernel::Font>& hgui::FontManager::add(const std::string& fontID, const std::string& fontPath)
{
	if (m_fonts.find(fontID) == m_fonts.end())
	{
		m_fonts[fontID] = std::make_shared<kernel::Font>(fontPath);
		return m_fonts[fontID];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A FONT WITH THE ID : " + fontID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Font>& hgui::FontManager::get(const std::string& fontID)
{
	if (m_fonts.find(fontID) != m_fonts.end())
	{
		return m_fonts[fontID];
	}
	else
	{
		throw std::exception(("THERE IS NO FONT WITH THE ID : " + fontID).c_str());
	}
}

void hgui::FontManager::destroy(const std::initializer_list<std::string>& fontsID)
{
	if (fontsID.size())
	{
		for (const auto& fontID : fontsID)
		{
			m_fonts.erase(fontID);
		}
	}
	else
	{
		m_fonts.clear();
	}
}
