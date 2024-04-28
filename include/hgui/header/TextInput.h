#pragma once

#include "Widget.h"

namespace hgui
{
	class TextInputManager;
	class KeyBoardManager;
}

namespace hgui::kernel
{
	class Label;
	class Font;
	class Drawer;

	class TextInput final : public Widget
	{
		friend TextInputManager;
		friend KeyBoardManager;

		using Function = std::variant<std::function<void()>, std::function<void(const std::shared_ptr<TextInput>&)>>;

	public:
		TextInput(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const std::pair<color, color>& colors, const std::pair<std::string, color>& placeHolder, const std::pair<color, std::chrono::milliseconds>& caret, Function onChange, HGUI_PRECISION cornerRadius, unsigned borderWidth);
		TextInput(const TextInput& textInput) = delete;
		TextInput(TextInput&& textInput) = default;

		~TextInput() override;

		TextInput& operator=(const TextInput& textInput) = delete;
		TextInput& operator=(TextInput&& textInput) = delete;

		void draw() const override;
		[[nodiscard]] bool is_inside(const point& point) const override;

		[[nodiscard]] unsigned get_caret_position_from_point(const point& point) const;
		void focus();
		void unfocus();

		[[nodiscard]] const std::string& get_value() const;
		[[nodiscard]] const std::pair<color, color>& get_colors() const;
		[[nodiscard]] const std::pair<std::string, color>& get_place_holder() const;
		[[nodiscard]] const Function& get_on_change_function() const;
		[[nodiscard]] bool is_focused() const;
		[[nodiscard]] unsigned get_caret_position() const;
		[[nodiscard]] const std::shared_ptr<Font>& get_font() const;
		[[nodiscard]] const color& get_text_color() const;
		[[nodiscard]] const std::pair<color, std::chrono::milliseconds>& get_caret() const;

		void set_position(const point& newPosition) override;
		void set_size(const size& newSize) override;
		void set_label(const std::shared_ptr<Label>& newText);
		void set_value(const std::string& value);
		void set_colors(const std::pair<color, color>& colors);
		void set_place_holder(const std::pair<std::string, color>& placeHolder);
		void set_on_change_function(const Function& onChange);
		void set_caret_position(unsigned caretPosition);
		void set_font(const std::shared_ptr<Font>& font) const;
		void set_text_color(const color& textColor);
		void set_caret(const std::pair<color, std::chrono::milliseconds>& caret);

	private:
		std::shared_ptr<Label> m_text;
		std::pair<color, color> m_colors;
		std::pair<std::string, color> m_placeHolder;
		Function m_onChange;
		HGUI_PRECISION m_cornerRadius;
		HGUI_PRECISION m_cornerAngularRadius;
		unsigned m_borderWidth;
		std::pair<glm::mat4, glm::mat4> m_modelMatrix;
		point m_inlineRectanglePosition;
		size m_inlineRectangleSize;
		HGUI_PRECISION m_inlineCornerRadius;
		color m_textColor;
		std::pair<color, std::chrono::milliseconds> m_caret;
		unsigned m_caretPosition;
		std::string m_value;
		unsigned m_textDisplayedIndex;
		mutable std::string m_taskID;
		std::unique_ptr<Drawer> m_drawer;

		void init_data();
		void set_text_placment_and_height() const;
		void update_text() const;
		void draw_caret() const;
		void display_caret() const;
		void increase_caret_position();
		void decrease_caret_position();
		void delete_char();
		void suppress_char();

		static inline std::weak_ptr<TextInput> m_focused;

		static void assert_is_displayable(const std::string& text, const std::shared_ptr<Font>& font);
		static unsigned get_advance(const std::string& text, const std::shared_ptr<Font>& font, unsigned size);
		static void text_input(GLFWwindow* window, unsigned int codepoint);

		friend void kernel::resources_cleaner();
	};
}
