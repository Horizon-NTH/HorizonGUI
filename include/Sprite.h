#pragma once

#include "Widget.h"

namespace hgui::kernel
{
	class Texture;

	class Sprite : public Widget
	{
	public:
		Sprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const size& size, const point& position, const color& color, HGUI_PRECISION rotation);
		Sprite(const Sprite& sprite) = delete;
		Sprite(Sprite&& sprite) = delete;

		~Sprite() override = default;

		Sprite& operator=(const Sprite& sprite) = delete;
		Sprite& operator=(Sprite&& sprite) = delete;

		void draw() const override;

		[[nodiscard]] bool is_inside(const point& point) const override;

		const std::shared_ptr<Texture>& get_texture() const;
		const color& get_color() const;
		HGUI_PRECISION get_rotation() const;

		void set_position(const point& newPosition) override;
		void set_texture(const std::shared_ptr<Texture>& newTexture);
		void set_color(const color& newColor);
		void set_rotation(HGUI_PRECISION rotation);

	private:
		std::shared_ptr<Texture> m_texture;
		glm::mat4 m_modelMatrix;
		color m_color;
		HGUI_PRECISION m_rotation;

		void init_data() const;
	};
}
