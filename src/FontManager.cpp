#include <hgui/header/FontManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Font>> hgui::FontManager::m_fonts;

const std::shared_ptr<hgui::kernel::Font>& hgui::FontManager::add(const std::string& fontName, const std::string& fontPath)
{
	if (m_fonts.find(fontName) == m_fonts.end())
	{
		m_fonts[fontName] = std::make_shared<kernel::Font>(fontPath);
		return m_fonts[fontName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A FONT WITH THE NAME : " + fontName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Font>& hgui::FontManager::get(const std::string& fontName)
{
	if (m_fonts.find(fontName) != m_fonts.end())
	{
		return m_fonts[fontName];
	}
	else
	{
		throw std::exception(("THERE IS NO FONT WITH THE NAME : " + fontName).c_str());
	}
}

void hgui::FontManager::delete_font(const std::initializer_list<std::string>& fonts)
{
	if (fonts.size())
	{
		for (const auto& font : fonts)
		{
			m_fonts.erase(font);
		}
	}
	else
	{
		m_fonts.clear();
	}
}
