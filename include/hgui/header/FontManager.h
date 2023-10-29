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
		static std::shared_ptr<kernel::Font> create(const std::string& fontPath);

	private:
		FontManager() = delete;
	};
#elif defined(HGUI_STATIC)
	class FontManager
	{
	public:
		static const std::shared_ptr<kernel::Font>& create(const std::string& fontID, const std::string& fontPath);
		static const std::shared_ptr<kernel::Font>& get(const std::string& fontID);
		static void destroy(const std::initializer_list<std::string>& fontsID);

	private:
		FontManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Font>> m_fonts;

		friend void kernel::resources_cleaner();
	};
#endif
}
