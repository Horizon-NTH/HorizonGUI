#include "../include/hgui/header/Buffer.h"
#include "../include/hgui/header/FrameBuffer.h"
#include "../include/hgui/header/RenderBuffer.h"
#include "../include/hgui/header/VertexArrayObject.h"
#include "../include/hgui/header/VertexBufferObject.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/Texture.h"
#include "../include/hgui/header/Image.h"

hgui::kernel::Buffer::Buffer(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) :
	m_shader(shader),
	m_frameBuffer(std::make_shared<FrameBuffer>()),
	m_renderBuffer(std::make_shared<RenderBuffer>()),
	m_texture(texture),
	m_VAO(std::make_shared<VertexArrayObject>()),
	m_VBO(std::make_shared<VertexBufferObject>())
{
	m_frameBuffer->bind();
	m_frameBuffer->attach_texture(m_texture);
	m_renderBuffer->bind();
	m_renderBuffer->create_depth_stencil();
	m_frameBuffer->attach_render_buffer(m_renderBuffer);
	if (m_frameBuffer->is_complete())
	{
		m_frameBuffer->unbind();
	}
	else
	{
		throw std::runtime_error(("ERROR WITH THE CREATION OF THE BUFFER : HGUI_FRAMEBUFFER_"
		                          + std::to_string(m_frameBuffer->get_id())).c_str());
	}
	init_data();
}

void hgui::kernel::Buffer::bind() const
{
	m_frameBuffer->bind();
	const auto& [size, channel, pixels] = m_texture->get_image()->get_data();
	glViewport(0, 0, static_cast<GLsizei>(size.width), static_cast<GLsizei>(size.height));
}

void hgui::kernel::Buffer::unbind() const
{
	m_frameBuffer->unbind();
	int width, height;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
	glViewport(0, 0, width, height);
}

void hgui::kernel::Buffer::show() const
{
	m_shader->use();
	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();
	m_shader->set_int("screenTexture", 0);
	m_VAO->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void hgui::kernel::Buffer::clear() const
{
	bind();
	glClear(GL_COLOR_BUFFER_BIT);
	unbind();
}

void hgui::kernel::Buffer::init_data() const
{
	constexpr float vertices[] = {
				-1.0f, 1.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f,
				1.0f, -1.0f, 1.0f, 0.0f,

				-1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, -1.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 1.0f, 1.0f
			};
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void*>(nullptr));
	m_VAO->unbind();
}
