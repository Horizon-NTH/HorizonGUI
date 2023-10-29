#pragma once

#include "Include.h"
#include "Shape.h"

namespace hgui::kernel::shape
{
	class Rectangle : public Shape
	{
	public:
		Rectangle(const point& topLeftVertex, const point& bottomRightVertex, const color& color, bool fill, float thickness);

		void draw(const std::shared_ptr<Shader>& shader) const override;

	private:
	};
}
