#include <hgui/header/SpriteManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Sprite>> hgui::SpriteManager::m_sprites;

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::create(const std::string& spriteName, const std::shared_ptr<kernel::Image>& image, const size& size, const point& position, const color& color, float angularRotation)
{
	if (m_sprites.find(spriteName) == m_sprites.end())
	{
		ResourceManager::load_texture("SPRITE_" + spriteName, image);
		m_sprites[spriteName] = std::make_shared<kernel::Sprite>(
			ResourceManager::get_shader(HGUI_SHADER_SPRITE), 
			ResourceManager::get_texture("SPRITE_" + spriteName), size, position, color, angularRotation);
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_sprites[spriteName]);
		return m_sprites[spriteName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A SPRITE WITH THE NAME : " + spriteName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::get(const std::string& spriteName)
{
	if (m_sprites.find(spriteName) != m_sprites.end())
	{
		return m_sprites[spriteName];
	}
	else
	{
		throw std::exception(("THERE IS NO SPRITE WITH THE NAME : " + spriteName).c_str());
	}
}

void hgui::SpriteManager::delete_sprites(const std::initializer_list<std::string>& spritesNames)
{
	if (spritesNames.size())
	{
		for (const std::string& sprite : spritesNames)
		{
			Widget::delete_widget(m_sprites[sprite]);
			m_sprites.erase(sprite);
		}
	}
	else
	{
		for (auto& sprite : m_sprites)
		{
			Widget::delete_widget(sprite.second);
		}
		m_sprites.clear();
	}
}
