#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "StraightLine.h"
#include "ShaderManager.h"

namespace hgui::kernel
{
	class Canvas;

	class Drawer
	{
		friend class Canvas;

	public:
		Drawer(const point& position, const size& size);
		Drawer(const Drawer& drawer) = delete;
		Drawer(Drawer&& drawer) = default;

		~Drawer() = default;

		Drawer& operator=(const Drawer& drawer) = delete;
		Drawer& operator=(Drawer&& drawer) = default;

		void draw_rectangle(const point& topLeftVertex, const point& rightBottomVertex, const color& color, bool fill = true, float thickness = 10.0f) const;
		void draw_triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, bool fill = true, float thickness = 10.0f) const;
		void draw_circle(const point& centerPosition, float radius, const color& color, bool fill = true, float thickness = 10.0f) const;
		void draw_line(const point& firstVertex, const point& secondVertex, const color& color, float thickness = 10.0f) const;
		[[nodiscard]] const std::shared_ptr<std::vector<std::shared_ptr<shape::Shape>>>& get_shapes() const;

		void draw() const;

	private:
		point m_position;
		size m_size;
		std::shared_ptr<std::vector<std::shared_ptr<shape::Shape>>> m_shapes;
	};
}