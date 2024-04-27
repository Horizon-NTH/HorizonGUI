#pragma once

#include "Widget.h"

namespace hgui
{
	typedef std::tuple<unsigned int, color, HGUI_PRECISION> TextOption;

	namespace kernel
	{
		class Font;

		class Label final : public Widget
		{
		public:
			Label(std::string text, const std::shared_ptr<Shader>& shader, const point& position, const std::shared_ptr<Font>& font, unsigned int fontSize, const color& color, bool align, HGUI_PRECISION scale, HGUI_PRECISION rotation);
			Label(const Label& label) = delete;
			Label(Label&& label) = default;

			~Label() override = default;

			Label& operator=(const Label& label) = delete;
			Label& operator=(Label&& labe) = default;

			[[nodiscard]] std::string get_text() const;
			[[nodiscard]] const color& get_color() const;
			[[nodiscard]] unsigned int get_font_size() const;
			[[nodiscard]] const std::shared_ptr<Font>& get_font() const;
			[[nodiscard]] bool is_align() const;
			[[nodiscard]] HGUI_PRECISION get_scale() const;
			[[nodiscard]] HGUI_PRECISION get_rotation() const;

			void set_font_size(unsigned int fontSize);
			void set_width(unsigned int newWidth);
			void set_height(unsigned int newHeight);
			void set_text(const std::string& newText);
			void set_color(const color& newColor);
			void set_font(const std::shared_ptr<Font>& font);
			void set_alignement(bool align);
			void set_scale(HGUI_PRECISION scale);
			void set_rotation(HGUI_PRECISION rotation);

			void draw() const override;

			[[nodiscard]] bool is_inside(const point& point) const override;

		private:
			std::string m_text;
			HGUI_PRECISION m_scale;
			unsigned int m_fontSize;
			std::shared_ptr<Font> m_font;
			color m_color;
			bool m_align;
			HGUI_PRECISION m_rotation;

			using Widget::set_size;
			void calcul_size();
			int get_max_bearing_y() const;
		};
	}
}
