#include <hgui/header/Shape.h>

hgui::kernel::shape::Shape::Shape(const bool fill, const float thickness, const hgui::color& color,
	const ShapeData& data) : m_VAO(std::make_shared<kernel::VertexArrayObject>()),
	m_VBO(std::make_shared<kernel::VertexBufferObject>()),
	m_fill(fill),
	m_thickness(thickness),
	m_color(color), m_data(data)

{
}

float hgui::kernel::shape::Shape::get_thickness() const
{
	return m_thickness;
}

bool hgui::kernel::shape::Shape::is_fill() const
{
	return m_fill;
}

const hgui::kernel::shape::ShapeData& hgui::kernel::shape::Shape::get_data() const
{
	return m_data;
}