#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Sprite.h"
#include "Image.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TagManager.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class SpriteManager
	{
	public:
		SpriteManager() = delete;
		~SpriteManager() = delete;
		SpriteManager(const SpriteManager& spriteManager) = delete;
		SpriteManager(SpriteManager&& spriteManager) = delete;

		SpriteManager& operator=(const SpriteManager& spriteManager) = delete;
		SpriteManager& operator=(SpriteManager&& spriteManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Sprite> create(const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, HGUI_PRECISION angularRotation = 0.0f);

	private:
		static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
#elif defined(HGUI_STATIC)
	class SpriteManager
	{
	public:
		SpriteManager() = delete;
		~SpriteManager() = delete;
		SpriteManager(const SpriteManager& bufferManager) = delete;
		SpriteManager(SpriteManager&& bufferManager) = delete;

		SpriteManager& operator=(const SpriteManager& bufferManager) = delete;
		SpriteManager& operator=(SpriteManager&& bufferManager) = delete;

		static const std::shared_ptr<kernel::Sprite>& create(const std::string& spriteID, const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, HGUI_PRECISION angularRotation = 0.0f);
		[[nodiscard]] static const std::shared_ptr<kernel::Sprite>& get(const std::string& spriteID);
		static void destroy(const std::initializer_list<std::string>& spritesID = {});

	private:
		static std::map<std::string, std::shared_ptr<kernel::Sprite>> m_sprites;

		friend void kernel::resources_cleaner();
	};
#endif
}