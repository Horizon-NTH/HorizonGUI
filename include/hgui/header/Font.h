#pragma once

#include "Include.h"
#include "Maths.hpp"

namespace hgui::kernel
{
	struct Character
	{
		GLuint textureID;
		hgui::size size;
		ivec2 bearing;
		unsigned int advance;
	};

	class Font
	{
	public:
		explicit Font(const std::string& fontPath);
		~Font() = default;

		[[nodiscard]] Character get_char(char character, unsigned int size) const;

		void load_font(unsigned int size);
		[[nodiscard]] bool is_load(unsigned int size) const;

	private:
		std::string m_fontPath;
		std::map<unsigned int, std::map<char, Character>> m_characters;
	};
}
