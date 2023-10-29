#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Shape.h"

namespace hgui::kernel::shape
{
	class Circle : public Shape
	{
	public:
		Circle(const point& centerPosition, float radius, const color& color, bool fill, float thickness);

		void draw(const std::shared_ptr<Shader>& shader) const override;

	private:
	};
}
