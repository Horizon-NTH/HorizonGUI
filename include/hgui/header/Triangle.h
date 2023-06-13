#pragma once

#include "Include.h"
#include "Shape.h"

namespace hgui
{
	namespace kernel
	{
		namespace shape
		{
			class Triangle : public Shape
			{
			public:
				Triangle(glm::vec2 firstVertex, glm::vec2 secondVertex, glm::vec2 thirdVertex, glm::vec3 color, bool fill, float thickness);

				void draw(const std::shared_ptr<Shader>& shader) const override;

			private:
			};
		}
	}
}