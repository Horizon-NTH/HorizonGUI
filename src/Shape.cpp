#include "../include/hgui/header/Shape.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"

hgui::kernel::shape::Shape::Shape(const bool fill, const float thickness, const color& color, ShapeData data) :
	m_VAO(std::make_shared<VertexArrayObject>()),
	m_VBO(std::make_shared<VertexBufferObject>()),
	m_fill(fill),
	m_thickness(thickness),
	m_color(color),
	m_data(std::move(data))
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

const hgui::color& hgui::kernel::shape::Shape::get_color() const
{
	return m_color;
}

const hgui::kernel::shape::ShapeData& hgui::kernel::shape::Shape::get_data() const
{
	return m_data;
}

void hgui::kernel::shape::Shape::set_color(const color& newColor)
{
	m_color = newColor;
}
