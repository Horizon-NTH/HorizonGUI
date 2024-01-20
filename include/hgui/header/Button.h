#pragma once

#include "Widget.h"

namespace hgui::kernel
{
	class Texture;
	class Label;

	class Button final : public Widget
	{
	public:
		Button(const std::function<void()>& function, const std::shared_ptr<Shader>& shader, const size& size, const point& position, const std::shared_ptr<Label>& text, const color& color, HGUI_PRECISION angularRotation, HGUI_PRECISION cornerRadius, const std::shared_ptr<Texture>& = nullptr);
		Button(const Button& button) = delete;
		Button(Button&& button) = default;

		~Button() override = default;

		Button& operator=(const Button& button) = delete;
		Button& operator=(Button&& button) = delete;

		void press() const;
		void draw() const override;
		[[nodiscard]] bool is_inside(const point& point) const override;

		[[nodiscard]] const state& get_state() const;

		void set_position(const point& newPosition) override;
		void set_size(const size& newSize) override;
		void set_state(const state& state);
		void set_color(const color& newColor);
		void set_textures(const std::shared_ptr<Texture>& texture);
		void set_text(const std::shared_ptr<Label>& text);

	protected:
		state m_state;
		std::function<void()> m_function;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<Label> m_text;
		HGUI_PRECISION m_cornerRadius;
		HGUI_PRECISION m_cornerAngularRadius;
		glm::mat4 m_modelMatrix;
		bool m_isTextDrawable;

		void init_data();
		void set_text_placment();
	};
}
