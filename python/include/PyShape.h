#pragma once

#include "Include.h"

class PyShape : hgui::kernel::shape::Shape
{
public:
	using Shape::Shape;

	void draw(const hgui::point& canvasPosition, const hgui::size& canvasSize) const override;
};

void init_shapes(const py::module& kernel);
