#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Image.h"
#include "TagManager.h"

namespace hgui
{
	namespace kernel
	{
		class Sprite;
		void resources_cleaner();
	}

	class SpriteManager
	{
	public:
		static const std::shared_ptr<kernel::Sprite>& create(const std::string& spriteName, const std::shared_ptr<kernel::Image>& image, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Sprite>& get(const std::string& spriteName);
		static void delete_sprites(const std::initializer_list<std::string>& spritesNames = {});

	private:
		SpriteManager();

		static std::map<std::string, std::shared_ptr<kernel::Sprite>> m_sprites;

		friend void kernel::resources_cleaner();
	};
}

