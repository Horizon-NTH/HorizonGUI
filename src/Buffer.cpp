#include <hgui/header/Buffer.h>

hgui::kernel::Buffer::Buffer(const std::shared_ptr<Shader> shader, const std::shared_ptr<kernel::Texture>& texture) :
	m_shader(shader), m_VAO(std::make_shared<VertexArrayObject>()), m_VBO(std::make_shared<VertexBufferObject>()),
	m_frameBuffer(std::make_shared<FrameBuffer>()), m_renderBuffer(std::make_shared<RenderBuffer>()), m_texture(texture)
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
		throw std::runtime_error(("ERROR WITH THE CREATION OF THE BUFFER : HGUI_FRAMEBUFFER_" + std::to_string(m_frameBuffer->get_id())).c_str());
	}
	init_data();
}

void hgui::kernel::Buffer::bind() const
{
	m_frameBuffer->bind();
}

void hgui::kernel::Buffer::unbind() const
{
	m_frameBuffer->unbind();
}

void hgui::kernel::Buffer::show() const
{
	m_shader->use();
	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();
	m_shader->set_1i("screenTexture", 0);
	m_VAO->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void hgui::kernel::Buffer::clear() const
{
	bind();
	glClear(GL_COLOR_BUFFER_BIT);
	unbind();
}

void hgui::kernel::Buffer::init_data()
{
	float vertices[] = {
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
	};
	m_VAO->bind();
	m_VBO->bind();
	m_VBO->set_data(vertices, sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	m_VAO->unbind();
}
