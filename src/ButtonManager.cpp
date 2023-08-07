#include <hgui/header/ButtonManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Button>> hgui::ButtonManager::m_buttons;

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::create(const std::string& buttonName, const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const color& color, const std::string& text, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, hgui::color, float>& textOptions, float angularRotation)
{
	if (m_buttons.find(buttonName) == m_buttons.end())
	{
		float cornerAngularRadius = std::min(size.width, size.height) * 0.5f;
		m_buttons[buttonName] = std::make_shared<kernel::Button>(function, 
			ResourceManager::get_shader(HGUI_SHADER_BUTTON), size, position, 
			font ? LabelManager::create("HGUI_BUTTON_TEXT_" + buttonName, text, position, font, textOptions) : nullptr, 
			color, angularRotation, cornerAngularRadius, texture);
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_buttons[buttonName]);
		Widget::bind(m_buttons[buttonName], inputs::OVER, [buttonName]() 
			{ 
				ButtonManager::get(buttonName)->set_state(state::HOVER); 
				CursorManager::set(HGUI_CURSOR_HAND); 
			});
		Widget::bind(m_buttons[buttonName], inputs::NOVER, [buttonName]() 
			{
				ButtonManager::get(buttonName)->set_state(state::NORMAL); 
				CursorManager::set(HGUI_CURSOR_ARROW); 
			});
		Widget::bind(m_buttons[buttonName], MouseCombinationAction(inputs::OVER, buttons::LEFT, actions::REPEAT), [buttonName]() 
			{
				ButtonManager::get(buttonName)->set_state(state::PRESS); 
			});
		Widget::bind(m_buttons[buttonName], MouseCombinationAction(inputs::OVER, buttons::LEFT, actions::RELEASE), [buttonName]() 
			{
				ButtonManager::get(buttonName)->press(); 
			});
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

void hgui::ButtonManager::delete_button(const std::initializer_list<std::string>& buttonsNames)
{
	if (buttonsNames.size())
	{
		for (const std::string& button : buttonsNames)
		{
			Widget::delete_widget(m_buttons[button]);
			m_buttons.erase(button);
		}
	}
	else
	{
		for (auto& button : m_buttons)
		{
			Widget::delete_widget(button.second);
		}
		m_buttons.clear();
	}
}
