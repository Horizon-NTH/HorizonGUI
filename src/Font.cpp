#include <hgui/header/Font.h>

hgui::kernel::Font::Font(const std::string& fontPath) :
	m_fontPath(fontPath)
{
}

hgui::kernel::Font::~Font()
{
}

hgui::kernel::Character hgui::kernel::Font::get_char(char character, unsigned int size) const
{
	if (m_characters.find(size) != m_characters.end() && m_characters.find(size)->second.find(character) != m_characters.find(size)->second.end())
	{
		return m_characters.find(size)->second.find(character)->second;
	}
	else
	{
		throw std::exception((std::string("FONT DOESN'T HAVE THE CHARACTER : " + character) + std::string(" IN THE SIZE : " + std::to_string(size))).c_str());
	}
}

void hgui::kernel::Font::load_font(unsigned int size)
{
	if (m_characters.find(size) == m_characters.end())
	{
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            throw std::runtime_error("ERROR FAILED TO INITIALZE FREETYPE");
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
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            m_characters[size].insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
	}
    else
    {
        throw std::exception(("THE FONT ALREADY EXIST IN THE SIZE : " + std::to_string(size)).c_str());
    }
}

bool hgui::kernel::Font::is_load(unsigned int size) const
{
    return m_characters.find(size) != m_characters.end();
}
