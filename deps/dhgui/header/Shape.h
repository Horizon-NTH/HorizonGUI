#pragma once

#include "Include.h"
#include "Maths.hpp"
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
				Shape(bool fill, float thickness, const point& center = {});

				virtual void draw(const std::shared_ptr<Shader>& shader) const = 0;

				float get_thickness() const;
				bool is_fill() const;
				const point& get_center() const;

			protected:
				std::shared_ptr<VertexArrayObject> m_VAO;
				std::shared_ptr<VertexBufferObject> m_VBO;
				bool m_fill;
				float m_thickness;
				point m_center;
			};
		}
	}
}

