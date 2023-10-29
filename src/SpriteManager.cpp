#include <hgui/header/SpriteManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Shader> hgui::SpriteManager::m_shader(nullptr);

std::shared_ptr<hgui::kernel::Sprite> hgui::SpriteManager::create(
	const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position,
	const color& color, float angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(
			R"(
				#version 330 core
				layout (location = 0) in vec4 vertex;

				out vec2 texturePosition;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					texturePosition = vertex.zw;
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex.xy, 0.0, 1.0);
				}
			)",
			R"(
				#version 330 core

				in vec2 texturePosition;
				out vec4 fragmentColor;

				uniform sampler2D sprite;
				uniform vec4 spriteColor;

				void main()
				{
					fragmentColor = vec4(spriteColor) * texture(sprite, texturePosition);
					if (fragmentColor.w < 1)
						discard;
				}
			)"
		);
	}
	std::shared_ptr<kernel::Sprite> widget;
	if (const auto data = std::get_if<std::shared_ptr<kernel::Image>>(&texture))
	{
		auto& image = *data;
		auto texture = TextureManager::create(image);
		widget = std::make_shared<kernel::Sprite>(
			m_shader, texture, size, position, color, angularRotation);
	}
	else if (const auto data = std::get_if<std::shared_ptr<kernel::Texture>>(&texture))
	{
		widget = std::make_shared<kernel::Sprite>(
			m_shader, *data, size, position, color, angularRotation);
	}
	Widget::m_widgets[TagManager::get_current_tag()].push_back(widget->weak_from_this());
	return widget;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Sprite>> hgui::SpriteManager::m_sprites;

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::create(const std::string& spriteID,
                                                                         const std::variant<
	                                                                         std::shared_ptr<kernel::Texture>, std::shared_ptr<
		                                                                         kernel::Image>>& texture, const size& size,
                                                                         const point& position, const color& color, float angularRotation)
{
	if (!m_sprites.contains(spriteID))
	{
		if (const auto data = std::get_if<std::shared_ptr<kernel::Image>>(&texture))
		{
			auto& texture_ptr = TextureManager::create("HGUI_SPRITE_" + spriteID, *data);
			m_sprites[spriteID] = std::make_shared<kernel::Sprite>(
				ShaderManager::get(HGUI_SHADER_SPRITE), texture_ptr, size, position, color, angularRotation);
		}
		else if (auto data = std::get_if<std::shared_ptr<kernel::Texture>>(&texture))
		{
			m_sprites[spriteID] = std::make_shared<kernel::Sprite>(
				ShaderManager::get(HGUI_SHADER_SPRITE),
				*data, size, position, color, angularRotation);
		}
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_sprites[spriteID]->weak_from_this());
		return m_sprites[spriteID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A SPRITE WITH THE ID : " + spriteID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Sprite>& hgui::SpriteManager::get(const std::string& spriteID)
{
	if (m_sprites.contains(spriteID))
	{
		return m_sprites[spriteID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO SPRITE WITH THE ID : " + spriteID).c_str());
	}
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
