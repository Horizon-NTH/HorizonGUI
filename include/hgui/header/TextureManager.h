#pragma once

#include "Include.h"
#include "Define.h"
#include "Texture.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class TextureManager
	{
	public:
		TextureManager() = delete;
		~TextureManager() = delete;
		TextureManager(const TextureManager& textureManager) = delete;
		TextureManager(TextureManager&& textureManager) = delete;

		TextureManager& operator=(const TextureManager& textureManager) = delete;
		TextureManager& operator=(TextureManager&& textureManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Texture> create(const std::shared_ptr<kernel::Image>& image);
	};
#elif defined(HGUI_STATIC)
	class TextureManager
	{
	public:
		TextureManager() = delete;
		~TextureManager() = delete;
		TextureManager(const TextureManager& bufferManager) = delete;
		TextureManager(TextureManager&& bufferManager) = delete;

		TextureManager& operator=(const TextureManager& bufferManager) = delete;
		TextureManager& operator=(TextureManager&& bufferManager) = delete;

		static std::shared_ptr<kernel::Texture>& create(const std::string& textureID, const std::shared_ptr<kernel::Image>& image);
		[[nodiscard]] static std::shared_ptr<kernel::Texture>& get(const std::string& textureID);
		static void destroy(const std::initializer_list<std::string>& texturesID);

	private:
		static std::map<std::string, std::shared_ptr<kernel::Texture>> m_textures;

		friend void kernel::resources_cleaner();
	};
#endif
}