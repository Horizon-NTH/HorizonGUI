#include <hgui/header/ButtonManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Button>> hgui::ButtonManager::m_buttons;

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::create(const std::string& buttonName, std::function<void()> function, glm::vec2 size, glm::vec2 position, std::shared_ptr<kernel::Texture> texture, glm::vec3 color, const std::string& text, const std::shared_ptr<kernel::Font>& font, std::tuple<unsigned int, glm::vec3, float> textOptions, float angularRotation)
{
	if (m_buttons.find(buttonName) == m_buttons.end())
	{
		float cornerAngularRadius = std::min(size.x, size.y) * 0.5f;
		m_buttons[buttonName] = std::make_shared<kernel::Button>(function, ResourceManager::get_shader(HGUI_SHADER_BUTTON), size, position, font ? TextManager::create("HGUI_BUTTON_TEXT_" + buttonName, text, position, font, textOptions) : nullptr, color, angularRotation, cornerAngularRadius, texture);
		WidgetManager::m_widgets[WidgetManager::m_currentTag].push_back(m_buttons[buttonName]);
		WidgetManager::bind(m_buttons[buttonName], input::OVER, [buttonName]() { ButtonManager::get(buttonName)->set_state(kernel::HOVER); CursorManager::set(HGUI_CURSOR_HAND); });
		WidgetManager::bind(m_buttons[buttonName], input::NOVER, [buttonName]() { ButtonManager::get(buttonName)->set_state(kernel::NORMAL); CursorManager::set(HGUI_CURSOR_ARROW); });
		WidgetManager::bind(m_buttons[buttonName], MouseCombinationAction(input::OVER, input::LEFT, input::REPEAT), [buttonName]() { ButtonManager::get(buttonName)->set_state(kernel::PRESS); });
		WidgetManager::bind(m_buttons[buttonName], MouseCombinationAction(input::OVER, input::LEFT, input::RELEASE), [buttonName]() { ButtonManager::get(buttonName)->press(); });
		return m_buttons[buttonName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A BUTTON WITH THE NAME : " + buttonName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::get(const std::string& buttonName)
{
	if (m_buttons.find(buttonName) != m_buttons.end())
	{
		return m_buttons[buttonName];
	}
	else
	{
		throw std::exception(("THERE IS NO BUTTON WITH THE NAME : " + buttonName).c_str());
	}
}

void hgui::ButtonManager::delete_button(std::initializer_list<std::string> buttonsNames)
{
	if (buttonsNames.size())
	{
		for (const std::string& str : buttonsNames)
		{
			WidgetManager::delete_widget(m_buttons[str]);
			m_buttons.erase(str);
		}
	}
	else
	{
		m_buttons.clear();
	}
}
