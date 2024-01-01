#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Widget.h"
#include "Font.h"
#include "Shader.h"

namespace hgui
{
	typedef std::tuple<unsigned int, color, HGUI_PRECISION> TextOption;

	namespace kernel
	{
		class Label final : public Widget
		{
		public:
			Label(std::string text, const std::shared_ptr<Shader>& shader, const point& position, const std::shared_ptr<Font>& font, unsigned int fontSize, const color& color, HGUI_PRECISION scale, HGUI_PRECISION angularRotation);
			Label(const Label& label) = delete;
			Label(Label&& label) = default;

			~Label() override = default;

			Label& operator=(const Label& label) = delete;
			Label& operator=(Label&& labe) = default;

			[[nodiscard]] std::string get_text() const;

			[[nodiscard]] unsigned int get_font_size() const;

			void set_font_size(unsigned int fontSize);
			void set_width(unsigned int newWidth);
			void set_height(unsigned int newHeight);
			void set_text(const std::string& newText);

			void draw() const override;

			[[nodiscard]] bool is_inside(const point& point) const override;

		private:
			std::string m_text;
			float m_scale;
			unsigned int m_fontSize;
			std::shared_ptr<Font> m_font;
		};
	}
}