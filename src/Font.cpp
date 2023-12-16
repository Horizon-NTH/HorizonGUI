#include <hgui/header/Font.h>

hgui::kernel::Font::Font(const std::string& fontPath) :
	m_fontPath(fontPath)
{
}

hgui::kernel::Character hgui::kernel::Font::get_char(const char character, const unsigned int size) const
{
	if (m_characters.contains(size) &&
		m_characters.find(size)->second.contains(character))
	{
		return m_characters.find(size)->second.find(character)->second;
	}
	else
	{
		throw std::runtime_error((std::string("FONT DOESN'T HAVE THE CHARACTER : " + character)
			+ std::string(" IN THE SIZE : " + std::to_string(size))).c_str());
	}
}

void hgui::kernel::Font::load_font(const unsigned int size)
{
	if (!m_characters.contains(size))
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			throw std::runtime_error("ERROR FAILED TO INITIALIZE FREETYPE");
		FT_Face face;
		if (FT_New_Face(ft, m_fontPath.c_str(), 0, &face))
			throw std::runtime_error(("ERROR FAILED TO LOAD FONT : " + m_fontPath).c_str());
		FT_Set_Pixel_Sizes(face, 0, size);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				throw std::runtime_error(std::string("ERROR FAILED TO LOAD GLYPH : " + static_cast<char>(c)).c_str());
			}
			ImageData data
			{
				.width = face->glyph->bitmap.width,
				.height = face->glyph->bitmap.rows,
				.channel = hgui::channels::GREYSCALE,
				.pixels = face->glyph->bitmap.buffer
			};
			auto texture = std::make_shared<Texture>(std::make_shared<Image>("", data),
				TextureOption
				{
					.wrap_s = GL_CLAMP_TO_BORDER,
					.wrap_t = GL_CLAMP_TO_BORDER
				});
			Character character
			{
				.texture = texture,
				.size = hgui::size(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				.bearing = ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				.advance = static_cast<unsigned int>(face->glyph->advance.x)
			};
			m_characters[size].insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
	else
	{
		throw std::runtime_error(("THE FONT ALREADY EXIST IN THE SIZE : " + std::to_string(size)).c_str());
	}
}

bool hgui::kernel::Font::is_load(const unsigned int size) const
{
	return m_characters.find(size) != m_characters.end();
}