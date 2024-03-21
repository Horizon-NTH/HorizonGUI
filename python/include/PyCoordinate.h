#pragma once

#include "Include.h"

class PyCoordinate : hgui::kernel::Coordinate<float>
{
public:
	using Coordinate::Coordinate;

	void update() override;
};
