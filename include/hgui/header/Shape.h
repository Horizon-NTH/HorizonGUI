#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Shader.h"

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
		Shape(bool fill, float thickness, const ShapeData& data);
		virtual ~Shape() = default;

		Shape(const Shape& shape) = default;
		Shape(Shape&& shape) = default;

		Shape& operator=(const Shape& shape) = default;
		Shape& operator=(Shape&& shape) = default;

		virtual void draw(const std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>& shaders) const = 0;

		[[nodiscard]] float get_thickness() const;
		[[nodiscard]] bool is_fill() const;
		[[nodiscard]] const ShapeData& get_data() const;

	protected:
		std::shared_ptr<VertexArrayObject> m_VAO;
		std::shared_ptr<VertexBufferObject> m_VBO;
		bool m_fill;
		float m_thickness;
		ShapeData m_data;
	};
}
