#include <hgui/header/SpriteManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Sprite>> hgui::SpriteManager::m_sprites;

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::create(const std::string& spriteID, const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color, float angularRotation)
{
	if (m_sprites.find(spriteID) == m_sprites.end())
	{
		if (auto data = std::get_if<std::shared_ptr<kernel::Image>>(&texture))
		{
			ResourceManager::load_texture("HGUI_SPRITE_" + spriteID, *data);
			m_sprites[spriteID] = std::make_shared<kernel::Sprite>(
				ResourceManager::get_shader(HGUI_SHADER_SPRITE),
				ResourceManager::get_texture("HGUI_SPRITE_" + spriteID), size, position, color, angularRotation);
		}
		else if (auto data = std::get_if<std::shared_ptr<kernel::Texture>>(&texture))
		{
			m_sprites[spriteID] = std::make_shared<kernel::Sprite>(
				ResourceManager::get_shader(HGUI_SHADER_SPRITE),
				*data, size, position, color, angularRotation);
		}
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_sprites[spriteID]->weak_from_this());
		return m_sprites[spriteID];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A SPRITE WITH THE ID : " + spriteID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::get(const std::string& spriteID)
{
	if (m_sprites.find(spriteID) != m_sprites.end())
	{
		return m_sprites[spriteID];
	}
	else
	{
		throw std::exception(("THERE IS NO SPRITE WITH THE ID : " + spriteID).c_str());
	}
}

void hgui::SpriteManager::destroy(const std::initializer_list<std::string>& spritesID)
{
	if (spritesID.size())
	{
		for (const std::string& spriteID : spritesID)
		{
			m_sprites.erase(spriteID);
		}
	}
	else
	{
		m_sprites.clear();
	}
}
