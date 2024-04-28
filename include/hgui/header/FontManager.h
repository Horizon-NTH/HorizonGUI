#pragma once

#include "Include.h"

namespace hgui
{
	namespace kernel
	{
		class Font;
	}

	class FontManager
	{
	public:
		FontManager() = delete;
		~FontManager() = delete;
		FontManager(const FontManager& fontManager) = delete;
		FontManager(FontManager&& fontManager) = delete;

		FontManager& operator=(const FontManager& fontManager) = delete;
		FontManager& operator=(FontManager&& fontManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Font> create(const std::string& fontPath);
	};
}
