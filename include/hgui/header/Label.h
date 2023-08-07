#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Widget.h"
#include "Font.h"
#include "Shader.h"
#include "MonitorManager.h"
#include "FontManager.h"
#include "WindowManager.h"

namespace hgui
{
	typedef std::tuple<unsigned int, vec3, float> TextOption;

	namespace kernel
	{
		class Label : public Widget
		{
		public:
			Label(const std::string& text, const std::shared_ptr<Shader>& shader, const point& position, const std::shared_ptr<Font>& font, unsigned int fontSize, const color& color, float scale);

			std::string get_text() const;
			void set_text(const std::string& newText);
			void set_size(const size& newSize);

			void draw() const override;

		private:
			std::string m_text;
			float m_scale;
			unsigned int m_fontSize;
			std::shared_ptr<Font> m_font;
		};
	}
}

