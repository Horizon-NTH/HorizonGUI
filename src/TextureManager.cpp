#include "../include/hgui/header/TextureManager.h"

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Texture> hgui::TextureManager::create(const std::shared_ptr<kernel::Image>& image)
{
	return std::make_shared<kernel::Texture>(image);
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Texture>> hgui::TextureManager::m_textures;

std::shared_ptr<hgui::kernel::Texture>& hgui::TextureManager::create(const std::string& textureID, const std::shared_ptr<kernel::Image>& image)
{
	if (!m_textures.contains(textureID))
	{
		m_textures[textureID] = std::make_shared<kernel::Texture>(image);
		return m_textures[textureID];
	}
	throw std::runtime_error(("THERE IS ALREADY A TEXTURE WITH THE ID : " + textureID).c_str());
}

std::shared_ptr<hgui::kernel::Texture>& hgui::TextureManager::get(const std::string& textureID)
{
	if (m_textures.contains(textureID))
	{
		return m_textures[textureID];
	}
	throw std::runtime_error(("THERE IS NO TEXTURE WITH THE ID : " + textureID).c_str());
}

void hgui::TextureManager::destroy(const std::initializer_list<std::string>& texturesID)
{
	if (texturesID.size())
	{
		for (const std::string& id : texturesID)
		{
			m_textures.erase(id);
		}
	}
	else
	{
		m_textures.clear();
	}
}
#endif
