#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Widget.h"
#include "Shader.h"
#include "Texture.h"

namespace hgui::kernel
{
	class Sprite final : public Widget
	{
	public:
		Sprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const size& size, const point& position, const color& color, HGUI_PRECISION angularRotation);
		Sprite(const Sprite& sprite) = delete;
		Sprite(Sprite&& sprite) = delete;

		~Sprite() override = default;

		Sprite& operator=(const Sprite& sprite) = delete;
		Sprite& operator=(Sprite&& sprite) = delete;

		void draw() const override;

		[[nodiscard]] bool is_inside(const point& point) const override;

		void set_position(const point& newPosition) override;
		void set_texture(const std::shared_ptr<Texture>& newTexture);

	private:
		std::shared_ptr<Texture> m_texture;
		glm::mat4 m_modelMatrix;

		void init_data() const;
	};
}
