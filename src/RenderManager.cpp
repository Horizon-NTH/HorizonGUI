#include <hgui/header/RenderManager.h>

std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, hgui::render::RenderOptions>> hgui::RenderManager::m_draws;
glm::vec3 hgui::RenderManager::m_backGroundColor;

void hgui::RenderManager::draw(std::vector<std::string> tags, render::RenderOptions postProcessingOption)
{
	for (const auto& tag : tags.size() ? tags : WidgetManager::get_tags())
	{
		if (postProcessingOption == render::CLASSIC)
		{
			if (std::find(m_draws.first.begin(), m_draws.first.end(), tag) == m_draws.first.end())
			{
				m_draws.first.push_back(tag);
			}
		}
		else
		{
			m_draws.second.second = postProcessingOption;
			if (std::find(m_draws.second.first.begin(), m_draws.second.first.end(), tag) == m_draws.second.first.end())
			{
				m_draws.second.first.push_back(tag);
			}
		}
	}
}

void hgui::RenderManager::loop()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(WindowManager::get_current_windowPTR()))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->clear();

		KeyBoardManager::process();
		MouseManager::process();

		render();

		glfwSwapBuffers(WindowManager::get_current_windowPTR());
		glfwPollEvents();
	}
	kernel::resources_cleaner();
	glfwTerminate();
}

void hgui::RenderManager::set_background_color(glm::vec3 newColor)
{
	m_backGroundColor = newColor;
	glClearColor(newColor.x, newColor.y, newColor.z, 1.0f);
}

glm::vec3 hgui::RenderManager::get_background_color()
{
	return m_backGroundColor;
}

void hgui::RenderManager::render()
{
	ResourceManager::get_shader(HGUI_SHADER_FRAMEBUFFER)->use().set_1i("type", m_draws.second.second);
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->bind();
	for (const std::string& tag : m_draws.second.first)
	{
		for (const auto& widget : WidgetManager::get_widgets(tag))
		{
			widget->draw();
		}
	}
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->unbind();
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->show();
	for (const std::string& tag : m_draws.first)
	{
		for (const auto& widget : WidgetManager::get_widgets(tag))
		{
			widget->draw();
		}
	}
}
