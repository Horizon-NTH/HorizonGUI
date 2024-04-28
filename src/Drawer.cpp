#include "../include/hgui/header/Drawer.h"
#include "../include/hgui/header/Rectangle.h"
#include "../include/hgui/header/Triangle.h"
#include "../include/hgui/header/Circle.h"
#include "../include/hgui/header/StraightLine.h"

hgui::kernel::Drawer::Drawer(point position, size size) :
	m_position(std::move(position)),
	m_size(std::move(size)),
	m_shapes(std::make_shared<std::map<std::string, std::shared_ptr<shape::Shape>>>())
{
}

const std::string& hgui::kernel::Drawer::draw_rectangle(const point& topLeftVertex, const point& rightBottomVertex, const color& color, bool fill, float thickness, const std::string& id) const
{
	if (m_shapes->contains(id))
	{
		throw std::runtime_error("THERE IS ALREADY A SHAPE WITH THE ID : " + id);
	}
	(*m_shapes)[id] = std::make_shared<shape::Rectangle>(point(m_position + topLeftVertex), point(m_position + rightBottomVertex),
		color, fill, thickness);
	m_order.push_back(id);
	return id;
}

const std::string& hgui::kernel::Drawer::draw_triangle(const point& firstVertex, const point& secondVertex, const point& thirdVertex, const color& color, bool fill, float thickness, const std::string& id) const
{
	if (m_shapes->contains(id))
	{
		throw std::runtime_error("THERE IS ALREADY A SHAPE WITH THE ID : " + id);
	}
	(*m_shapes)[id] = std::make_shared<shape::Triangle>(point(m_position + firstVertex), point(m_position + secondVertex),
		point(m_position + thirdVertex), color, fill, thickness);
	m_order.push_back(id);
	return id;
}

const std::string& hgui::kernel::Drawer::draw_circle(const point& centerPosition, float radius, const color& color, bool fill, float thickness, const std::string& id) const
{
	if (m_shapes->contains(id))
	{
		throw std::runtime_error("THERE IS ALREADY A SHAPE WITH THE ID : " + id);
	}
	(*m_shapes)[id] = std::make_shared<shape::Circle>(point(m_position + centerPosition), radius, color, fill, thickness);
	m_order.push_back(id);
	return id;
}

const std::string& hgui::kernel::Drawer::draw_line(const point& firstVertex, const point& secondVertex, const color& color, float thickness, const std::string& id) const
{
	if (m_shapes->contains(id))
	{
		throw std::runtime_error("THERE IS ALREADY A SHAPE WITH THE ID : " + id);
	}
	(*m_shapes)[id] = std::make_shared<shape::StraightLine>(point(m_position + firstVertex), point(m_position + secondVertex), color, thickness);
	m_order.push_back(id);
	return id;
}

const std::shared_ptr<std::map<std::string, std::shared_ptr<hgui::kernel::shape::Shape>>>& hgui::kernel::Drawer::get_shapes() const
{
	return m_shapes;
}

std::pair<hgui::point, hgui::size> hgui::kernel::Drawer::get_placement() const
{
	return std::make_pair(m_position, m_size);
}

void hgui::kernel::Drawer::set_placement(const point& position, const size& size)
{
	m_position = position;
	m_size = size;
}

void hgui::kernel::Drawer::draw() const
{
	std::vector<std::string> idToDelete;
	for (const auto& id : m_order)
	{
		if (m_shapes->contains(id))
		{
			(*m_shapes)[id]->draw(m_position, m_size);
		}
		else
		{
			idToDelete.push_back(id);
		}
	}
	for (const auto& pastedID : idToDelete)
	{
		m_order.erase(std::begin(std::ranges::remove(m_order, pastedID)), m_order.end());
	}
}
