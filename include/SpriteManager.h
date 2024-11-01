#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Image;
		class GIF;
		class Texture;
		class Shader;
		class AnimatedSprite;
		class Sprite;
	}

	class SpriteManager
	{
	public:
		SpriteManager() = delete;
		~SpriteManager() = delete;
		SpriteManager(const SpriteManager& spriteManager) = delete;
		SpriteManager(SpriteManager&& spriteManager) = delete;

		SpriteManager& operator=(const SpriteManager& spriteManager) = delete;
		SpriteManager& operator=(SpriteManager&& spriteManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Sprite> create(const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, HGUI_PRECISION rotation = 0.0f);
		[[nodiscard]] static std::shared_ptr<kernel::AnimatedSprite> create(const std::shared_ptr<kernel::GIF>& gif, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, HGUI_PRECISION rotation = 0.0f);

	private:
		inline static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}
