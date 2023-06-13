#pragma once

#include "Include.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "StraightLine.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "Define.h"

namespace hgui
{
	namespace kernel
	{
		class Drawer
		{
		public:
			Drawer(glm::vec2 position, glm::vec2 size);

			void draw_rectangle(glm::vec2 topLeftVertex, glm::vec2 rightBottomVertex, glm::vec3 color, bool fill = true, float thickness = 1.0f);
			void draw_triangle(glm::vec2 firstVertex, glm::vec2 secondVertex, glm::vec2 thirdVertex, glm::vec3 color, bool fill = true, float thickness = 1.0f);
			void draw_circle(glm::vec2 centerPosition, float radius, glm::vec3 color, bool fill = true, float thickness = 1.0f);
			void draw_line(glm::vec2 firstVertex, glm::vec2 secondVertex, glm::vec3 color, float thickness = 1.0f);
			const std::vector<std::shared_ptr<shape::Shape>>& get_shapes() const;

			void draw() const;

		private:
			glm::vec2 m_position;
			glm::vec2 m_size;
			std::vector<std::shared_ptr<shape::Shape>> m_shapes;
		};
	}
}