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
	class SpriteManager
	{
	public:
		static std::shared_ptr<kernel::Sprite> create(const std::variant<std::shared_ptr<kernel::Texture>, std::shared_ptr<kernel::Image>>& texture, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, float angularRotation = 0.0f);

	private:
		SpriteManager() = delete;

		static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}
