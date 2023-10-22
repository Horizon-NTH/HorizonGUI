#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Widget.h"
#include "Font.h"
#include "Shader.h"

namespace hgui
{
	typedef std::tuple<unsigned int, color, float> TextOption;

	namespace kernel
	{
		class Label : public Widget
		{
		public:
			Label(const std::string& text, const std::shared_ptr<Shader>& shader, const point& position, const std::shared_ptr<Font>& font, unsigned int fontSize, const color& color, float scale);

			std::string get_text() const;
			void set_text(const std::string& newText);

			unsigned int get_font_size() const;
			void set_font_size(unsigned int fontSize);

			void set_width(unsigned int newWidth);
			void set_height(unsigned int newHeight);

			void draw() const override;

		private:
			std::string m_text;
			float m_scale;
			unsigned int m_fontSize;
			std::shared_ptr<Font> m_font;
		};
	}
}

