#include <hgui/header/Shape.h>

hgui::kernel::shape::Shape::Shape(bool fill, float thickness, const point& center) :
	m_VAO(std::make_shared<kernel::VertexArrayObject>()), m_VBO(std::make_shared<kernel::VertexBufferObject>()),
	m_fill(fill), m_thickness(thickness), m_center(center)
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

const hgui::point& hgui::kernel::shape::Shape::get_center() const
{
	return m_center;
}
