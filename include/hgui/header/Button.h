#pragma once

#include "Widget.h"

namespace hgui::kernel
{
	class Texture;
	class Label;

	class Button final : public Widget
	{
	public:
		Button(const std::function<void()>& function, const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const std::tuple<color, color, color>& colors, HGUI_PRECISION cornerRadius, bool blurrOnHover, const std::shared_ptr<Texture>& = nullptr);
		Button(const Button& button) = delete;
		Button(Button&& button) = default;

		~Button() override = default;

		Button& operator=(const Button& button) = delete;
		Button& operator=(Button&& button) = delete;

		void press() const;
		void draw() const override;
		[[nodiscard]] bool is_inside(const point& point) const override;

		[[nodiscard]] const state& get_state() const;
		[[nodiscard]] const std::tuple<color, color, color>& get_color() const;
		[[nodiscard]] const std::shared_ptr<Texture>& get_texture() const;
		[[nodiscard]] const std::string& get_text() const;
		[[nodiscard]] const std::shared_ptr<Label>& get_label() const;
		[[nodiscard]] const std::function<void()>& get_function() const;
		[[nodiscard]] bool get_blurr_on_hover() const;

		void set_position(const point& newPosition) override;
		void set_size(const size& newSize) override;
		void set_state(const state& state);
		void set_color(const std::tuple<color, color, color>& newColors);
		void set_texture(const std::shared_ptr<Texture>& texture);
		void set_label(const std::shared_ptr<Label>& label);
		void set_text(const std::string& text);
		void set_function(const std::function<void()>& function);
		void set_blurr_on_hover(bool blurrOnHover);

	protected:
		state m_state;
		std::function<void()> m_function;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<Label> m_text;
		HGUI_PRECISION m_cornerRadius;
		HGUI_PRECISION m_cornerAngularRadius;
		glm::mat4 m_modelMatrix;
		std::tuple<color, color, color> m_colors;
		bool m_blurrOnHover;
		std::string m_textValue;

		void init_data();
		void set_text_placment() const;
		void truncate_text() const;
	};
}
