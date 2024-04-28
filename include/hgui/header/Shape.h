#pragma once

#include "Coordinate.hpp"

namespace hgui::kernel
{
	class VertexBufferObject;
	class VertexArrayObject;
}

namespace hgui::kernel::shape
{
	typedef std::variant<
		std::pair<point, point>,					// For rectangle
		std::pair<point, HGUI_PRECISION>,			// For circle
		std::array<point, 3>,						// For triangle
		std::tuple<point, point, HGUI_PRECISION>	// For line
	> ShapeData;

	class Shape
	{
	public:
		Shape(bool fill, float thickness, const color& color, ShapeData data);
		virtual ~Shape() = default;

		Shape(const Shape& shape) = default;
		Shape(Shape&& shape) = default;

		Shape& operator=(const Shape& shape) = default;
		Shape& operator=(Shape&& shape) = default;

		virtual void draw(const point& canvasPosition, const size& canvasSize) const = 0;

		[[nodiscard]] float get_thickness() const;
		[[nodiscard]] bool is_fill() const;
		[[nodiscard]] const color& get_color() const;
		[[nodiscard]] const ShapeData& get_data() const;

		void set_color(const color& newColor);

	protected:
		std::shared_ptr<VertexArrayObject> m_VAO;
		std::shared_ptr<VertexBufferObject> m_VBO;
		bool m_fill;
		float m_thickness;
		color m_color;
		ShapeData m_data;
	};
}
