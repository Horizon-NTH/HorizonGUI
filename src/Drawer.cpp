#include <hgui/header/Drawer.h>

hgui::kernel::Drawer::Drawer(glm::vec2 position, glm::vec2 size) :
	m_position(position), m_size(size)
{
}

void hgui::kernel::Drawer::draw_rectangle(glm::vec2 topLeftVertex, glm::vec2 rightBottomVertex, glm::vec3 color, bool fill, float thickness)
{
	m_shapes.push_back(std::make_shared<shape::Rectangle>(m_position + topLeftVertex, m_position + rightBottomVertex, color, fill, thickness));
}

void hgui::kernel::Drawer::draw_triangle(glm::vec2 firstVertex, glm::vec2 secondVertex, glm::vec2 thirdVertex, glm::vec3 color, bool fill, float thickness)
{
	m_shapes.push_back(std::make_shared<shape::Triangle>(m_position + firstVertex, m_position + secondVertex, m_position + thirdVertex, color, fill, thickness));
}

void hgui::kernel::Drawer::draw_circle(glm::vec2 centerPosition, float radius, glm::vec3 color, bool fill, float thickness)
{
	m_shapes.push_back(std::make_shared<shape::Circle>(m_position + centerPosition, radius, color, fill, thickness));
}

void hgui::kernel::Drawer::draw_line(glm::vec2 firstVertex, glm::vec2 secondVertex, glm::vec3 color, float thickness)
{
	m_shapes.push_back(std::make_shared<shape::StraightLine>(m_position + firstVertex, m_position + secondVertex, color, thickness));
}

const std::vector<std::shared_ptr<hgui::kernel::shape::Shape>>& hgui::kernel::Drawer::get_shapes() const
{
	return m_shapes;
}

void hgui::kernel::Drawer::draw() const
{
	for (const auto& shape : m_shapes)
	{
		shape->draw(hgui::ResourceManager::get_shader(HGUI_SHADER_CANVA));
	}
}