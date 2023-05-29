#pragma once

#include "Include.h"
#include "Widget.h"
#include "Font.h"
#include "Shader.h"
#include "MonitorManager.h"
#include "FontManager.h"
#include "WindowManager.h"

namespace hgui
{
	typedef std::tuple<std::shared_ptr<kernel::Font>, unsigned int, glm::vec3, float> TextOption;

	namespace kernel
	{
		class TextArea : public Widget
		{
		public:
			TextArea(const std::string& text, const std::shared_ptr<Shader>& shader, glm::vec2 position, const std::shared_ptr<Font> font, unsigned int fontSize, glm::vec3 color, float scale);

			std::string get_text() const;
			void set_text(const std::string& newText);
			void set_size(glm::vec2 newSize);

			void draw() const override;

		private:
			std::string m_text;
			float m_scale;
			unsigned int m_fontSize;
			std::shared_ptr<Font> m_font;
		};
	}
}

