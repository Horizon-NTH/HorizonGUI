#pragma once

#include "Shape.h"

namespace hgui::kernel
{
	class Shader;
}

namespace hgui::kernel::shape
{
	class Rectangle final : public Shape
	{
	public:
		Rectangle(const point& topLeftVertex, const point& bottomRightVertex, const color& color, bool fill, float thickness);
		~Rectangle() override = default;

		Rectangle(const Rectangle& rectangle) = delete;
		Rectangle(Rectangle&& rectangle) = delete;

		Rectangle& operator=(const Rectangle& rectangle) = delete;
		Rectangle& operator=(Rectangle&& rectangle) = delete;

		void draw(const point& canvasPosition, const size& canvasSize) const override;

	private:
		inline static std::shared_ptr<Shader> m_shader{};
	};
}
