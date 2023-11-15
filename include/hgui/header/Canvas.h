#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Widget.h"
#include "Drawer.h"

namespace hgui::kernel
{
	class Canvas final : public Widget
	{
	public:
		Canvas(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const color& color,
		       float angularRotation);

		void draw() const override;

		void set_position(const point& newPosition) override;

		[[nodiscard]] const std::shared_ptr<kernel::Drawer>& get_drawer() const;

	private:
		glm::mat4 m_modelMatrix;
		float m_angularRotation;
		std::shared_ptr<kernel::Drawer> m_drawer;

		void init_data() const;
	};
}
