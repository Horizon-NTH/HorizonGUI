#pragma once

#include "Include.h"
#include "Define.h"
#include "Font.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class FontManager
	{
	public:
		FontManager() = delete;
		~FontManager() = delete;
		FontManager(const FontManager& bufferManager) = delete;
		FontManager(FontManager&& bufferManager) = delete;

		FontManager& operator=(const FontManager& bufferManager) = delete;
		FontManager& operator=(FontManager&& bufferManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Font> create(const std::string& fontPath);
	};
#elif defined(HGUI_STATIC)
	class FontManager
	{
	public:
		FontManager() = delete;
		~FontManager() = delete;
		FontManager(const FontManager& bufferManager) = delete;
		FontManager(FontManager&& bufferManager) = delete;

		FontManager& operator=(const FontManager& bufferManager) = delete;
		FontManager& operator=(FontManager&& bufferManager) = delete;

		static const std::shared_ptr<kernel::Font>& create(const std::string& fontID, const std::string& fontPath);
		[[nodiscard]] static const std::shared_ptr<kernel::Font>& get(const std::string& fontID);
		static void destroy(const std::initializer_list<std::string>& fontsID);

	private:
		static std::map<std::string, std::shared_ptr<kernel::Font>> m_fonts;

		friend void kernel::resources_cleaner();
	};
#endif
}
