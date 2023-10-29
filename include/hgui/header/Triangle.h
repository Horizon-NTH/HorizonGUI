#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Shape.h"

namespace hgui::kernel::shape
{
	class Triangle : public Shape
	{
	public:
		Triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, bool fill,
		         float thickness);

		void draw(const std::shared_ptr<Shader>& shader) const override;

	private:
	};
}
