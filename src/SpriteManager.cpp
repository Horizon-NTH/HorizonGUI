#include "../include/hgui/header/SpriteManager.h"
#include "../include/hgui/header/Sprite.h"
#include "../include/hgui/header/AnimatedSprite.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/TextureManager.h"

#if defined(HGUI_DYNAMIC)
#include "../include/hgui/header/GLSL.h"

std::shared_ptr<hgui::kernel::Sprite> hgui::SpriteManager::create(const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color, HGUI_PRECISION angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_SPRITE, HGUI_GLSL_FRAGMENT_SPRITE);
	}
	std::shared_ptr<kernel::Sprite> widget;
	if (const auto data = std::get_if<std::shared_ptr<kernel::Image>>(&texture))
	{
		auto& image = *data;
		auto texture_ptr = TextureManager::create(image);
		widget = std::make_shared<kernel::Sprite>(
			m_shader, texture_ptr, size, position, color, angularRotation);
	}
	else if (const auto texture_ptr = std::get_if<std::shared_ptr<kernel::Texture>>(&texture))
	{
		widget = std::make_shared<kernel::Sprite>(
			m_shader, *texture_ptr, size, position, color, angularRotation);
	}
	return widget;
}

std::shared_ptr<hgui::kernel::AnimatedSprite> hgui::SpriteManager::create(const std::shared_ptr<kernel::GIF>& gif, const size& size, const point& position, const color& color, float angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_SPRITE, HGUI_GLSL_FRAGMENT_SPRITE);
	}
	auto widget = std::make_shared<kernel::AnimatedSprite>(m_shader, gif, size, position, color, angularRotation);
	return widget;
}

#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Sprite>> hgui::SpriteManager::m_sprites;

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::create(const std::string& spriteID, const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color, HGUI_PRECISION angularRotation)
{
	if (!m_sprites.contains(spriteID))
	{
		if (const auto image = std::get_if<std::shared_ptr<kernel::Image>>(&texture))
		{
			auto& texture_ptr = TextureManager::create("HGUI_SPRITE_" + spriteID, *image);
			m_sprites[spriteID] = std::make_shared<kernel::Sprite>(
				ShaderManager::get(HGUI_SHADER_SPRITE), texture_ptr, size, position, color, angularRotation);
		}
		else if (auto texture_ptr = std::get_if<std::shared_ptr<kernel::Texture>>(&texture_ptr))
		{
			m_sprites[spriteID] = std::make_shared<kernel::Sprite>(
				ShaderManager::get(HGUI_SHADER_SPRITE),
				*texture_ptr, size, position, color, angularRotation);
		}
		return m_sprites[spriteID];
	}
	throw std::runtime_error(("THERE IS ALREADY A SPRITE WITH THE ID : " + spriteID).c_str());
}

std::shared_ptr<hgui::kernel::AnimatedSprite> hgui::SpriteManager::create(const std::string& spriteID, const std::shared_ptr<kernel::GIF>& gif, const size& size, const point& position, const color& color, float angularRotation)
{
	if (!m_sprites.contains(spriteID))
	{
		m_sprites[spriteID] = std::make_shared<kernel::AnimatedSprite>(ShaderManager::get(HGUI_SHADER_SPRITE), gif, size, position, color, angularRotation);
		return std::dynamic_pointer_cast<kernel::AnimatedSprite>(m_sprites[spriteID]);
	}
	throw std::runtime_error(("THERE IS ALREADY A SPRITE WITH THE ID : " + spriteID).c_str());
}

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::get(const std::string& spriteID)
{
	if (m_sprites.contains(spriteID))
	{
		return m_sprites[spriteID];
	}
	throw std::runtime_error(("THERE IS NO SPRITE WITH THE ID : " + spriteID).c_str());
}

void hgui::SpriteManager::destroy(const std::initializer_list<std::string>& spritesID)
{
	if (spritesID.size())
	{
		for (const std::string& id : spritesID)
		{
			m_sprites.erase(id);
		}
	}
	else
	{
		m_sprites.clear();
	}
}
#endif
