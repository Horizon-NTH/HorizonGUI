#pragma once

#include "Include.h"
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
				StraightLine(glm::vec2 firstVertex, glm::vec2 secondVertex, glm::vec3 color, float thickness);

				void draw(const std::shared_ptr<Shader>& shader) const override;

			private:
			};
		}
	}
}