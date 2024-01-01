#include <hgui/header/Sprite.h>

hgui::kernel::Sprite::Sprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const size& size, const point& position, const color& color, const HGUI_PRECISION angularRotation) :
	Widget(shader, size, position, color, angularRotation),
	m_texture(texture),
	m_modelMatrix(1.0)
{
	init_data();
	set_position(position);
}

void hgui::kernel::Sprite::draw() const
{
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	m_shader->use().set_mat4("modelMatrix", m_modelMatrix)
		.set_vec4("spriteColor", vec4(m_color))
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
	const auto A = point::rotate(hgui::point(m_position.x, m_position.y), center, m_angularRotation),
		B = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y), center, m_angularRotation),
		C = point::rotate(hgui::point(m_position.x + m_size.width, m_position.y + m_size.height), center, m_angularRotation),
		D = point::rotate(hgui::point(m_position.x, m_position.y + m_size.height), center, m_angularRotation);

	return point::is_in_rectangle(A, B, D, point);
}

void hgui::kernel::Sprite::set_position(const point& newPosition)
{
	Widget::set_position(newPosition);
	m_modelMatrix = glm::mat4(1.0);
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(m_position.x, m_position.y, 0.0f));
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(0.5f * m_size.width, 0.5f * m_size.height, 0.0f));
	m_modelMatrix = rotate(m_modelMatrix, glm::radians(m_angularRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = translate(m_modelMatrix, glm::vec3(-0.5f * m_size.width, -0.5f * m_size.height, 0.0f));
	m_modelMatrix = scale(m_modelMatrix, glm::vec3(m_size.width, m_size.height, 1.0f));
}

void hgui::kernel::Sprite::set_texture(const std::shared_ptr<Texture>& newTexture)
{
	m_texture = newTexture;
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