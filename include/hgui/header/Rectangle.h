#pragma once

#include "Include.h"
#include "Shape.h"

namespace hgui::kernel::shape
{
	class Rectangle final : public Shape
	{
	public:
		Rectangle(const point& topLeftVertex, const point& bottomRightVertex, const color& color, bool fill, float thickness);
		~Rectangle() override = default;

		Rectangle(const Rectangle& rectangle) = default;
		Rectangle(Rectangle&& rectangle) = default;

		Rectangle& operator=(const Rectangle& rectangle) = default;
		Rectangle& operator=(Rectangle&& rectangle) = default;

		void draw(const std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>& shaders) const override;
	};
}
