#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Shader.h"
#include "ShaderManager.h"

namespace hgui::kernel::shape
{
	typedef std::variant<
		std::pair<hgui::point, hgui::point>,					// For rectangle
		std::pair<hgui::point, HGUI_PRECISION>,					// For circle
		std::array<hgui::point, 3>,								// For triangle
		std::tuple<hgui::point, hgui::point, HGUI_PRECISION>	// For line
	> ShapeData;

	class Shape
	{
	public:
		Shape(bool fill, float thickness, const hgui::color& color, const ShapeData& data);
		virtual ~Shape() = default;

		Shape(const Shape& shape) = default;
		Shape(Shape&& shape) = default;

		Shape& operator=(const Shape& shape) = default;
		Shape& operator=(Shape&& shape) = default;

		virtual void draw(const hgui::point& canvasPosition, const hgui::size& canvasSize, float canvasRotation = 0.f) const = 0;

		[[nodiscard]] float get_thickness() const;
		[[nodiscard]] bool is_fill() const;
		[[nodiscard]] const hgui::color& get_color() const;
		[[nodiscard]] const ShapeData& get_data() const;

	protected:
		std::shared_ptr<VertexArrayObject> m_VAO;
		std::shared_ptr<VertexBufferObject> m_VBO;
		bool m_fill;
		float m_thickness;
		hgui::color m_color;
		ShapeData m_data;
	};
}