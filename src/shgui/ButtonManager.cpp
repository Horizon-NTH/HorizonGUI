#include <hgui/header/ButtonManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Button>> hgui::ButtonManager::m_buttons;

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::create(const std::string& buttonID, const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const color& color, float borderRadius,const std::string& text, const std::shared_ptr<kernel::Font>& font, const hgui::color& textColor, float angularRotation)
{
	if (m_buttons.find(buttonID) == m_buttons.end())
	{
		float cornerAngularRadius = std::min(std::min(size.width, size.height) * 0.5f, borderRadius);
		m_buttons[buttonID] = std::make_shared<kernel::Button>(function,
			ShaderManager::get(HGUI_SHADER_BUTTON), size, position,
			font ? LabelManager::create("HGUI_BUTTON_TEXT_" + buttonID, text, position, font, textOptions) : nullptr,
			color, angularRotation, cornerAngularRadius, texture);
		auto& widgets = Widget::m_widgets[TagManager::get_current_tag()];
		widgets.insert(widgets.size() ? widgets.end() - 1 : widgets.end(), m_buttons[buttonID]->weak_from_this());
		Widget::bind(m_buttons[buttonID], inputs::OVER, [buttonID]()
			{
				ButtonManager::get(buttonID)->set_state(state::HOVER);
				CursorManager::get(HGUI_CURSOR_HAND)->use();
			});
		Widget::bind(m_buttons[buttonID], inputs::NOVER, [buttonID]()
			{
				ButtonManager::get(buttonID)->set_state(state::NORMAL);
				hgui::TaskManager::program(std::chrono::milliseconds(0), [&]()
					{
						auto isHover = []() -> bool
						{
							for (auto& tag : Widget::m_bindedTags)
							{
								for (auto& widget : Widget::m_widgets[tag])
								{
									if (auto button = std::dynamic_pointer_cast<kernel::Button>(widget.lock()))
									{
										if (button->get_state() == state::HOVER ||
											button->get_state() == state::PRESS)
										{
											return true;
										}
									}
								}
							}
							return false;
						};
						if (!isHover())
						{
							CursorManager::get(HGUI_CURSOR_ARROW)->use();
						}
					});
			});
		Widget::bind(m_buttons[buttonID], std::make_tuple(inputs::OVER, buttons::LEFT, actions::REPEAT), [buttonID]()
			{
				ButtonManager::get(buttonID)->set_state(state::PRESS);
			});
		Widget::bind(m_buttons[buttonID], std::make_tuple(inputs::OVER, buttons::LEFT, actions::RELEASE), [buttonID]()
			{
				ButtonManager::get(buttonID)->press();
				hgui::TaskManager::program(std::chrono::milliseconds(0), [&]()
					{
						auto isHover = []() -> bool
						{
							for (auto& tag : Widget::m_bindedTags)
							{
								for (auto& widget : Widget::m_widgets[tag])
								{
									if (auto button = std::dynamic_pointer_cast<kernel::Button>(widget.lock()))
									{
										if (button->get_state() == state::HOVER ||
											button->get_state() == state::PRESS)
										{
											return true;
										}
									}
								}
							}
							return false;
						};
						if (!isHover())
						{
							CursorManager::get(HGUI_CURSOR_ARROW)->use();
						}
					});
			});
		return m_buttons[buttonID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A BUTTON WITH THE ID : " + buttonID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::get(const std::string& buttonID)
{
	if (m_buttons.find(buttonID) != m_buttons.end())
	{
		return m_buttons[buttonID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO BUTTON WITH THE ID : " + buttonID).c_str());
	}
}

void hgui::ButtonManager::destroy(const std::initializer_list<std::string>& buttonsID)
{
	if (buttonsID.size())
	{
		for (const std::string& buttonID : buttonsID)
		{
			m_buttons.erase(buttonID);
		}
	}
	else
	{
		m_buttons.clear();
	}
}
