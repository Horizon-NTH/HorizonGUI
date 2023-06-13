#pragma once

#include "Include.h"
#include "Shape.h"

namespace hgui
{
	namespace kernel
	{
		namespace shape
		{
			class Rectangle : public Shape
			{
			public:
				Rectangle(glm::vec2 topLeftVertex, glm::vec2 bottomRightVertex, glm::vec3 color, bool fill, float thickness);

				void draw(const std::shared_ptr<Shader>& shader) const override;

			private:
			};
		}
	}
}