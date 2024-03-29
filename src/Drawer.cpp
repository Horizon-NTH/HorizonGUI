#include "../include/hgui/header/Drawer.h"
#include "../include/hgui/header/Rectangle.h"
#include "../include/hgui/header/Triangle.h"
#include "../include/hgui/header/Circle.h"
#include "../include/hgui/header/StraightLine.h"

hgui::kernel::Drawer::Drawer(point position, size size, const HGUI_PRECISION rotation) :
	m_position(std::move(position)),
	m_size(std::move(size)),
	m_rotation(rotation),
	m_shapes(std::make_shared<std::vector<std::shared_ptr<shape::Shape>>>())
{
}

void hgui::kernel::Drawer::draw_rectangle(const point& topLeftVertex, const point& rightBottomVertex, const color& color, bool fill, float thickness) const
{
	m_shapes->push_back(std::make_shared<shape::Rectangle>(point(m_position + topLeftVertex), point(m_position + rightBottomVertex),
		color, fill, thickness));
}

void hgui::kernel::Drawer::draw_triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, bool fill, float thickness) const
{
	m_shapes->push_back(std::make_shared<shape::Triangle>(point(m_position + firstVertex), point(m_position + secondVertex),
		point(m_position + thirdVertex), color, fill, thickness));
}

void hgui::kernel::Drawer::draw_circle(const point& centerPosition, float radius, const color& color, bool fill, float thickness) const
{
	m_shapes->push_back(std::make_shared<shape::Circle>(point(m_position + centerPosition), radius, color, fill, thickness));
}

void hgui::kernel::Drawer::draw_line(const point& firstVertex, const point& secondVertex, const color& color, float thickness) const
{
	m_shapes->push_back(
		std::make_shared<shape::StraightLine>(point(m_position + firstVertex), point(m_position + secondVertex), color, thickness));
}

const std::shared_ptr<std::vector<std::shared_ptr<hgui::kernel::shape::Shape>>>& hgui::kernel::Drawer::get_shapes() const
{
	return m_shapes;
}

void hgui::kernel::Drawer::draw() const
{
	for (const auto& shape : *m_shapes)
	{
		shape->draw(m_position, m_size, m_rotation);
	}
}
