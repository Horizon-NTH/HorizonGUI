#pragma once

#include "Widget.h"

namespace hgui::kernel
{
	class Drawer;

	class Canvas final : public Widget
	{
	public:
		Canvas(const std::shared_ptr<Shader>& shader, const size& size, const point& position, const color& color);
		Canvas(const Canvas& canvas) = delete;
		Canvas(Canvas&& canvas) = default;

		~Canvas() override = default;

		Canvas& operator=(const Canvas& canvas) = delete;
		Canvas& operator=(Canvas&& canvas) = default;

		void draw() const override;

		void set_position(const point& newPosition) override;
		void set_size(const size& newSize) override;

		[[nodiscard]] bool is_inside(const point& point) const override;

		[[nodiscard]] const std::shared_ptr<Drawer>& get_drawer() const;

	private:
		glm::mat4 m_modelMatrix;
		std::shared_ptr<Drawer> m_drawer;
		color m_color;

		void init_data() const;
	};
}
