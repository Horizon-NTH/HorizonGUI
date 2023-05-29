#pragma once

#include "Include.h"
#include "Define.h"
#include "WidgetManager.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Image.h"
#include "Tools.h"

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
		static const std::shared_ptr<kernel::Sprite>& create(const std::string& spriteName, const std::shared_ptr<kernel::Image>& image, glm::vec2 size, glm::vec2 position, glm::vec3 color = glm::vec3(1.0), float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Sprite>& get(const std::string& spriteName);
		static void delete_sprites(std::initializer_list<std::string> spritesNames = {});

	private:
		SpriteManager();

		static std::map<std::string, std::shared_ptr<kernel::Sprite>> m_sprites;

		friend void kernel::resources_cleaner();
	};
}

