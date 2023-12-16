#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Texture.h"

namespace hgui::kernel
{
	struct Character
	{
		std::shared_ptr<Texture> texture;
		hgui::size size;
		ivec2 bearing;
		unsigned int advance;
	};

	class Font
	{
	public:
		explicit Font(const std::string& fontPath);
		Font(const Font& font) = delete;
		Font(Font&& font) = default;

		~Font() = default;

		Font& operator=(const Font& font) = delete;
		Font& operator=(Font&& font) = default;

		[[nodiscard]] Character get_char(char character, unsigned int size) const;

		void load_font(unsigned int size);
		[[nodiscard]] bool is_load(unsigned int size) const;

	private:
		std::string m_fontPath;
		std::map<unsigned int, std::map<char, Character>> m_characters;
	};
}