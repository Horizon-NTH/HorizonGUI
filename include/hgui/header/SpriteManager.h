#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "TagManager.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Image.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	class SpriteManager
	{
	public:
		static const std::shared_ptr<kernel::Sprite>& create(const std::string& spriteID, const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Sprite>& get(const std::string& spriteID);
		static void destroy(const std::initializer_list<std::string>& spritesID = {});

	private:
		SpriteManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Sprite>> m_sprites;

		friend void kernel::resources_cleaner();
	};
}

