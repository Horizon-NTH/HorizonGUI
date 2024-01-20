#pragma once

#include "Coordinate.hpp"

namespace hgui::kernel
{
	namespace shape
	{
		class Shape;
	}

	class Canvas;

	class Drawer
	{
		friend class Canvas;

	public:
		Drawer(point  position, size  size, HGUI_PRECISION angularRotation = 0.f);
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
		HGUI_PRECISION m_rotation;
		std::shared_ptr<std::vector<std::shared_ptr<shape::Shape>>> m_shapes;
	};
}
