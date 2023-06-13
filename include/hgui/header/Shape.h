#pragma once

#include "Include.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Shader.h"

namespace hgui
{
	namespace kernel
	{
		namespace shape
		{
			class Shape
			{
			public:
				Shape(bool fill, float thickness, glm::vec2 center = glm::vec2(0.0));

				virtual void draw(const std::shared_ptr<Shader>& shader) const = 0;

				float get_thickness() const;
				bool is_fill() const;
				glm::vec2 get_center() const;

			protected:
				std::shared_ptr<VertexArrayObject> m_VAO;
				std::shared_ptr<VertexBufferObject> m_VBO;
				bool m_fill;
				float m_thickness;
				glm::vec2 m_center;
			};
		}
	}
}

