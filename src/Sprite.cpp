#include "../include/hgui/header/Sprite.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/Texture.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"

hgui::kernel::Sprite::Sprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const size& size, const point& position, const color& color, const HGUI_PRECISION rotation) :
    Widget(shader, size, position),
    m_texture(texture),
    m_modelMatrix(1.0),
    m_color(color),
    m_rotation(rotation)
{
    init_data();
    Sprite::set_position(position);
}

void hgui::kernel::Sprite::draw() const
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
            .set_vec4("spriteColor", m_color)
            .set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.f, -1.0f, 1.0f))
            .set_int("sprite", 0);
    if (m_texture)
    {
        glActiveTexture(GL_TEXTURE0);
        m_texture->bind();
    }
    m_VAO->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_VAO->unbind();
}

bool hgui::kernel::Sprite::is_inside(const point& point) const
{
    const hgui::point center(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f);
    const auto A = point::rotate(hgui::point(m_position.x, m_position.y), center, m_rotation),
            B = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y), center, m_rotation),
            D = point::rotate(hgui::point(m_position.x, m_position.y + m_size.height), center, m_rotation);

    return point::is_in_rectangle(A, B, D, point);
}

const std::shared_ptr<hgui::kernel::Texture>& hgui::kernel::Sprite::get_texture() const
{
    return m_texture;
}

const hgui::color& hgui::kernel::Sprite::get_color() const
{
    return m_color;
}

HGUI_PRECISION hgui::kernel::Sprite::get_rotation() const
{
    return m_rotation;
}

void hgui::kernel::Sprite::set_position(const point& newPosition)
{
    Widget::set_position(newPosition);
    m_modelMatrix = glm::mat4(1.0);
    m_modelMatrix = translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, 0.0f));
    m_modelMatrix = translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
    m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
    m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
}

void hgui::kernel::Sprite::set_texture(const std::shared_ptr<Texture>& newTexture)
{
    m_texture = newTexture;
}

void hgui::kernel::Sprite::set_color(const color& newColor)
{
    m_color = newColor;
}

void hgui::kernel::Sprite::set_rotation(const HGUI_PRECISION rotation)
{
    m_rotation = rotation;
    set_position(m_position);
}

void hgui::kernel::Sprite::init_data() const
{
    constexpr float vertices[] = {
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,

                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f
            };
    m_VAO->bind();
    m_VBO->bind();
    m_VBO->set_data(vertices, sizeof(vertices));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
    m_VAO->unbind();
}
