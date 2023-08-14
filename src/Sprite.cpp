#include <hgui/header/Sprite.h>

hgui::kernel::Sprite::Sprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const size& size, const point& position, const color& color, float angularRoation) :
    Widget(shader, size, position, color), m_texture(texture), m_angularRotation(angularRoation), m_modelMatrix(1.0)
{
    init_data();
    set_position(position);
}

hgui::kernel::Sprite::~Sprite()
{
}

void hgui::kernel::Sprite::draw() const
{
    kernel::Window* window = static_cast<kernel::Window*>(glfwGetWindowUserPointer(WindowManager::get_current_windowPTR()));
    m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
        .set_vec3("spriteColor", m_color)
        .set_mat4("projectionMatrix", glm::ortho(0.0f, static_cast<float>(window->get_size().width), 
            static_cast<float>(window->get_size().height), 0.f, -1.0f, 1.0f))
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

void hgui::kernel::Sprite::set_position(const point& newPosition)
{
    Widget::set_position(newPosition);
    m_modelMatrix = glm::mat4(1.0);
    m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, 0.0f));
    m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_angularRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
}

void hgui::kernel::Sprite::set_texture(const std::shared_ptr<Texture>& newTexture)
{
    m_texture = newTexture;
}

void hgui::kernel::Sprite::init_data()
{
    float vertices[] = {
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
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    m_VAO->unbind();
}
