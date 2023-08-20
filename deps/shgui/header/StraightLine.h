#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Shape.h"

namespace hgui
{
	namespace kernel
	{
		namespace shape
		{
			class StraightLine : public Shape
			{
			public:
				StraightLine(const point& firstVertex, const point& secondVertex, const color& color, float thickness);

				void draw(const std::shared_ptr<Shader>& shader) const override;

			private:
			};
		}
	}
}