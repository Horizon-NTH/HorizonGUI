#include <hgui/header/Widget.h>

hgui::kernel::Widget::Widget(const std::shared_ptr<Shader>& shader, glm::vec2 size, glm::vec2 position, glm::vec3 color) :
    m_shader(shader), m_size(size), m_position(position), m_color(color),
    m_VAO(std::make_shared<VertexArrayObject>()), m_VBO(std::make_shared<VertexBufferObject>())
{
    if (!m_shader)
    {
        throw std::exception("ERROR NEED SHADER TO CREATE A WIDGET");
    }
}

hgui::kernel::Widget::~Widget()
{
}

glm::vec2 hgui::kernel::Widget::get_position() const
{
    return m_position;
}

void hgui::kernel::Widget::set_position(glm::vec2 newPosition)
{
    m_position = newPosition;
}

glm::vec2 hgui::kernel::Widget::get_size() const
{
    return m_size;
}
