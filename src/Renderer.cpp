#include "../include/hgui/header/Renderer.h"
#include "../include/hgui/header/GLSL.h"
#include "../include/hgui/header/TagManager.h"
#include "../include/hgui/header/Shader.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/KeyBoardManager.h"
#include "../include/hgui/header/MouseManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/Widget.h"
#include "../include/hgui/header/Buffer.h"
#include "../include/hgui/header/BufferManager.h"
#include "../include/hgui/header/Timer.h"

#if defined(HGUI_DYNAMIC)
std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, hgui::effects>> hgui::Renderer::m_draws;
hgui::color hgui::Renderer::m_backGroundColor;
std::shared_ptr<hgui::kernel::Buffer> hgui::Renderer::m_frameBuffer(nullptr);
std::shared_ptr<hgui::kernel::Shader> hgui::Renderer::m_frameBufferShader(nullptr);
std::function<void()> hgui::Renderer::m_drawCallBack(nullptr);
std::shared_ptr<hgui::Timer> hgui::Renderer::m_timer(std::make_shared<Timer>());
double hgui::Renderer::m_deltaTime{};

void hgui::Renderer::draw(const std::vector<std::string>& tags, const effects& postProcessingOption)
{
	if (postProcessingOption == effects::CLASSIC)
	{
		m_draws.first.clear();
	}
	else
	{
		m_draws.second.first.clear();
	}
	for (const auto& tag : !tags.empty() ? tags : TagManager::get_tags())
	{
		if (postProcessingOption == effects::CLASSIC)
		{
			if (std::ranges::find(m_draws.first, tag) == m_draws.first.end())
			{
				m_draws.first.push_back(tag);
			}
		}
		else
		{
			m_draws.second.second = postProcessingOption;
			if (std::ranges::find(m_draws.second.first, tag) == m_draws.second.first.end())
			{
				m_draws.second.first.push_back(tag);
			}
		}
	}
}

void hgui::Renderer::loop()
{
	static bool alreadyInLoop = false;
	if (!alreadyInLoop)
	{
		alreadyInLoop = true;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_frameBufferShader = ShaderManager::create(HGUI_GLSL_VERTEX_BUFFER, HGUI_GLSL_FRAGMENT_BUFFER);
		buffer_update();
		while (!glfwWindowShouldClose(glfwGetCurrentContext()))
		{
			// Delta time calculation
			m_deltaTime = m_timer->get_time();
			m_timer->restart();

			glClear(GL_COLOR_BUFFER_BIT);
			m_frameBuffer->clear();

			KeyBoardManager::process();
			MouseManager::process();
			TaskManager::process();

			render();

			if (m_drawCallBack)
			{
				m_drawCallBack();
			}

			glfwSwapBuffers(glfwGetCurrentContext());
			glfwPollEvents();
		}
		kernel::resources_cleaner();
		glfwTerminate();
		alreadyInLoop = false;
	}
}

void hgui::Renderer::set_background_color(const color& newColor)
{
	m_backGroundColor = newColor;
	glClearColor(newColor.r, newColor.g, newColor.b, 0.5f);
}

void hgui::Renderer::set_draw_callback(const std::function<void()>& function)
{
	m_drawCallBack = function;
}

const hgui::color& hgui::Renderer::get_background_color()
{
	return m_backGroundColor;
}

void hgui::Renderer::render()
{
	m_frameBufferShader->use().set_int("type", static_cast<int>(m_draws.second.second));
	m_frameBuffer->bind();
	for (const std::string& tag : m_draws.second.first)
	{
		for (const auto& wwidget : kernel::Widget::get_widgets(tag))
		{
			if (const auto widget = wwidget.lock())
			{
				widget->draw();
			}
		}
	}
	m_frameBuffer->unbind();
	m_frameBuffer->show();
	for (const std::string& tag : m_draws.first)
	{
		for (const auto& wwidget : kernel::Widget::get_widgets(tag))
		{
			if (const auto widget = wwidget.lock())
			{
				widget->draw();
			}
		}
	}
}

void hgui::Renderer::buffer_update()
{
	if (m_frameBufferShader)
	{
		m_frameBuffer = BufferManager::create(m_frameBufferShader, size(100_em));
	}
}

#elif defined(HGUI_STATIC)
std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, hgui::effects>> hgui::Renderer::m_draws;
hgui::color hgui::Renderer::m_backGroundColor;
std::function<void()> hgui::Renderer::m_drawCallBack(nullptr);

void hgui::Renderer::draw(const std::vector<std::string>& tags, const effects& postProcessingOption)
{
	if (postProcessingOption == effects::CLASSIC)
	{
		m_draws.first.clear();
	}
	else
	{
		m_draws.second.first.clear();
	}
	for (const auto& tag : !tags.empty() ? tags : TagManager::get_tags())
	{
		if (postProcessingOption == effects::CLASSIC)
		{
			if (std::ranges::find(m_draws.first, tag) == m_draws.first.end())
			{
				m_draws.first.push_back(tag);
			}
		}
		else
		{
			m_draws.second.second = postProcessingOption;
			if (std::ranges::find(m_draws.second.first, tag) == m_draws.second.first.end())
			{
				m_draws.second.first.push_back(tag);
			}
		}
	}
}

void hgui::Renderer::loop()
{
	static bool alreadyInLoop = false;
	if (!alreadyInLoop)
	{
		alreadyInLoop = true;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		buffer_update();
		while (!glfwWindowShouldClose(glfwGetCurrentContext()))
		{
			// Delta time calculation
			m_deltaTime = m_timer->get_time();
			m_timer->restart();

			glClear(GL_COLOR_BUFFER_BIT);
			BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->clear();

			KeyBoardManager::process();
			MouseManager::process();
			TaskManager::process();

			render();

			if (m_drawCallBack)
			{
				m_drawCallBack();
			}

			glfwSwapBuffers(glfwGetCurrentContext());
			glfwPollEvents();
		}
		kernel::resources_cleaner();
		glfwTerminate();
		alreadyInLoop = false;
	}
}

void hgui::Renderer::set_background_color(const color& newColor)
{
	m_backGroundColor = newColor;
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

const hgui::color& hgui::Renderer::get_background_color()
{
	return m_backGroundColor;
}

void hgui::Renderer::set_draw_callback(const std::function<void()>& function)
{
	m_drawCallBack = function;
}

void hgui::Renderer::render()
{
	ShaderManager::get(HGUI_SHADER_FRAMEBUFFER)->use().set_int("type", static_cast<int>(m_draws.second.second));
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->bind();
	for (const std::string& tag : m_draws.second.first)
	{
		for (const auto& wwidget : kernel::Widget::get_widgets(tag))
		{
			if (const auto widget = wwidget.lock())
			{
				widget->draw();
			}
		}
	}
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->unbind();
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->show();
	for (const std::string& tag : m_draws.first)
	{
		for (const auto& wwidget : kernel::Widget::get_widgets(tag))
		{
			if (const auto widget = wwidget.lock())
			{
				widget->draw();
			}
		}
	}
}

void hgui::Renderer::buffer_update()
{
	if (ShaderManager::get(HGUI_SHADER_FRAMEBUFFER))
	{
		BufferManager::destroy({HGUI_FRAMEBUFFER_POST_PROCESSING});
		BufferManager::create(HGUI_FRAMEBUFFER_POST_PROCESSING,
			ShaderManager::get(HGUI_SHADER_FRAMEBUFFER), size(100_em));
	}
}
#endif
