#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Widget.h"
#include "Texture.h"
#include "Shader.h"
#include "Label.h"

namespace hgui::kernel
{
	class Button : public Widget
	{
	public:
		Button(const std::function<void()>& function, const std::shared_ptr<Shader>& shader, const size& size, const point& position,
		       const std::shared_ptr<Label>& text, const color& color, float angularRotation, float cornerAngularRadius,
		       const std::shared_ptr<Texture>& = nullptr);

		void press() const;
		void draw() const override;

		void set_position(const point& newPosition) override;
		void set_state(const state& state);
		[[nodiscard]] const state& get_state() const;
		void set_textures(const std::shared_ptr<Texture>& texture);

	protected:
		state m_state;
		std::function<void()> m_function;
		std::shared_ptr<Texture> m_texture;
		std::shared_ptr<Label> m_text;
		float m_cornerAngularRadius;
		float m_angularRotation;
		glm::mat4 m_modelMatrix;

		void init_data();
	};
}
