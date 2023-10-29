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
		Sprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const size& size, const point& position,
		       const color& color, float angularRotation);

		~Sprite() override = default;

		void draw() const override;

		void set_position(const point& newPosition) override;

		void set_texture(const std::shared_ptr<Texture>& newTexture);

	private:
		std::shared_ptr<Texture> m_texture;
		float m_angularRotation;
		glm::mat4 m_modelMatrix;

		void init_data() const;
	};
}
