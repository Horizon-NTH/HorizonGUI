#pragma once

#include "Include.h"
#include "Define.h"
#include "Texture.h"

namespace hgui
{
	class TextureManager
	{
	public:
		static std::shared_ptr<kernel::Texture>& create(const std::string& textureID, const std::shared_ptr<kernel::Image>& image);
		static std::shared_ptr<kernel::Texture>& get(const std::string& textureID);
		static void destroy(const std::initializer_list<std::string>& texturesID);

	private:
		TextureManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Texture>> m_textures;

		friend void kernel::resources_cleaner();
	};
}