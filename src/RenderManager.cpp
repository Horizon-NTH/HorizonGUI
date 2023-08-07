#include <hgui/header/RenderManager.h>

std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, hgui::effects>> hgui::RenderManager::m_draws;
hgui::color hgui::RenderManager::m_backGroundColor;

void hgui::RenderManager::draw(const std::vector<std::string>& tags, const effects& postProcessingOption)
{
	if (postProcessingOption == effects::CLASSIC)
	{
		m_draws.first.clear();
	}
	else
	{
		m_draws.second.first.clear();
	}
	for (const auto& tag : tags.size() ? tags : TagManager::get_tags())
	{
		if (postProcessingOption == effects::CLASSIC)
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
		TaskManager::process();

		render();

		glfwSwapBuffers(WindowManager::get_current_windowPTR());
		glfwPollEvents();
	}
	kernel::resources_cleaner();
	glfwTerminate();
}

void hgui::RenderManager::set_background_color(const color& newColor)
{
	m_backGroundColor = newColor;
	glClearColor(newColor.r, newColor.g, newColor.b, 1.0f);
}

const hgui::color& hgui::RenderManager::get_background_color()
{
	return m_backGroundColor;
}

void hgui::RenderManager::render()
{
	ResourceManager::get_shader(HGUI_SHADER_FRAMEBUFFER)->use().set_int("type", static_cast<int>(m_draws.second.second));
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->bind();
	for (const std::string& tag : m_draws.second.first)
	{
		for (const auto& widget : Widget::get_widgets(tag))
		{
			widget->draw();
		}
	}
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->unbind();
	BufferManager::get(HGUI_FRAMEBUFFER_POST_PROCESSING)->show();
	for (const std::string& tag : m_draws.first)
	{
		for (const auto& widget : Widget::get_widgets(tag))
		{
			widget->draw();
		}
	}
}
