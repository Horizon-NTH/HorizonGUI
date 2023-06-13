#pragma once

#include "Include.h"
#include "Shape.h"

namespace hgui
{
	namespace kernel
	{
		namespace shape
		{
			class Circle : public Shape
			{
			public:
				Circle(glm::vec2 centerPosition, float radius, glm::vec3 color, bool fill, float thickness);

				void draw(const std::shared_ptr<Shader>& shader) const override;

			private:
			};
		}
	}
}