#pragma once

#include "Include.h"
#include "Font.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	class FontManager
	{
	public:
		static const std::shared_ptr<kernel::Font>& add(const std::string& fontName, const std::string& fontPath);
		static const std::shared_ptr<kernel::Font>& get(const std::string& fontName);
		static void delete_font(const std::initializer_list<std::string>& fonts);

	private:
		FontManager();

		static std::map<std::string, std::shared_ptr<kernel::Font>> m_fonts;

		friend void kernel::resources_cleaner();
	};
}

