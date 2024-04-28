#pragma once

#include "Include.h"

namespace hgui
{
	namespace kernel
	{
		class Image;
		class Texture;
	}

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
}
