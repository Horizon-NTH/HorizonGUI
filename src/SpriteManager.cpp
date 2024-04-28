#include "../include/hgui/header/SpriteManager.h"
#include "../include/hgui/header/Sprite.h"
#include "../include/hgui/header/AnimatedSprite.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/TextureManager.h"
#include "../include/hgui/header/GLSL.h"

std::shared_ptr<hgui::kernel::Sprite> hgui::SpriteManager::create(const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color, HGUI_PRECISION rotation)
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
			m_shader, texture_ptr, size, position, color, rotation);
	}
	else if (const auto texture_ptr = std::get_if<std::shared_ptr<kernel::Texture>>(&texture))
	{
		widget = std::make_shared<kernel::Sprite>(
			m_shader, *texture_ptr, size, position, color, rotation);
	}
	return widget;
}

std::shared_ptr<hgui::kernel::AnimatedSprite> hgui::SpriteManager::create(const std::shared_ptr<kernel::GIF>& gif, const size& size, const point& position, const color& color, float rotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_SPRITE, HGUI_GLSL_FRAGMENT_SPRITE);
	}
	auto widget = std::make_shared<kernel::AnimatedSprite>(m_shader, gif, size, position, color, rotation);
	return widget;
}
