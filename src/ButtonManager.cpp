#include <hgui/header/ButtonManager.h>
#include <hgui/header/GLSL.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Shader> hgui::ButtonManager::m_shader(nullptr);
std::shared_ptr<hgui::kernel::Cursor> hgui::ButtonManager::m_cursor(nullptr);

std::shared_ptr<hgui::kernel::Button> hgui::ButtonManager::create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const color& color, const float borderRadius, const std::string& text, const std::shared_ptr<kernel::Font>& font, const hgui::color& textColor, HGUI_PRECISION angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_BUTTON, HGUI_GLSL_FRAGMENT_BUTTON);
	}
	auto widget = std::make_shared<kernel::Button>(function,
		m_shader, size, position,
		font ?
		LabelManager::create(text, position, font, TextOption(12u, textColor, 1.0f), angularRotation) :
		nullptr,
		color, angularRotation, borderRadius, texture);
	auto& widgets = Widget::m_widgets[TagManager::get_current_tag()];
	widgets.insert(!widgets.empty() ? widgets.end() - 1 : widgets.end(), widget->weak_from_this());
	std::weak_ptr<kernel::Button> wwidget = std::static_pointer_cast<kernel::Button>(widget->shared_from_this());
	widget->bind(inputs::OVER, [wwidget]()
		{
			wwidget.lock()->set_state(state::HOVER);
			if (!m_cursor)
			{
				m_cursor = CursorManager::create(cursors::HAND);
			}
			m_cursor->use();
		});
	widget->bind(inputs::NOVER, [wwidget]()
		{
			wwidget.lock()->set_state(state::NORMAL);
			hgui::TaskManager::program(std::chrono::milliseconds(0), [&]()
				{
					if (auto isHover = []() -> bool
						{
							for (auto& tag : Widget::m_bindedTags)
							{
								for (auto& ptr : Widget::m_widgets[tag])
								{
									if (const auto button = std::dynamic_pointer_cast<
										kernel::Button>(ptr.lock()))
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
						}; !isHover())
					{
						m_cursor = nullptr;
					}
				});
		});
	widget->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::REPEAT), [wwidget]()
		{
			wwidget.lock()->set_state(state::PRESS);
		});
	widget->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::RELEASE), [wwidget]()
		{
			wwidget.lock()->press();
			hgui::TaskManager::program(std::chrono::milliseconds(0), [&]()
				{
					if (auto isHover = []() -> bool
						{
							for (auto& tag : Widget::m_bindedTags)
							{
								for (auto& ptr : Widget::m_widgets[tag])
								{
									if (const auto button = std::dynamic_pointer_cast<
										kernel::Button>(ptr.lock()))
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
						}; !isHover())
					{
						m_cursor = nullptr;
					}
				});
		});
	return widget;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Button>> hgui::ButtonManager::m_buttons;

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::create(const std::string& buttonID, const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const color& color, float borderRadius, const std::string& text, const std::shared_ptr<kernel::Font>& font, const hgui::color& textColor, HGUI_PRECISION angularRotation)
{
	if (!m_buttons.contains(buttonID))
	{
		float cornerAngularRadius = std::min(std::min(size.width, size.height) * 0.5f, borderRadius);
		m_buttons[buttonID] = std::make_shared<kernel::Button>(function,
			ShaderManager::get(HGUI_SHADER_BUTTON), size, position,
			font ?
			LabelManager::create(
				"HGUI_BUTTON_TEXT_" + buttonID, text, position, font,
				{ 12, textColor, 1.0f }) :
			nullptr,
			color, angularRotation, cornerAngularRadius, texture);
		auto& widgets = Widget::m_widgets[TagManager::get_current_tag()];
		widgets.insert(!widgets.empty() ? widgets.end() - 1 : widgets.end(), m_buttons[buttonID]->weak_from_this());
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
						if (auto isHover = []() -> bool
							{
								for (auto& tag : Widget::m_bindedTags)
								{
									for (auto& widget : Widget::m_widgets[tag])
									{
										if (const auto button = std::dynamic_pointer_cast<
											kernel::Button>(
												widget.lock()))
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
							}; !isHover())
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
						if (auto isHover = []() -> bool
							{
								for (auto& tag : Widget::m_bindedTags)
								{
									for (auto& widget : Widget::m_widgets[tag])
									{
										if (const auto button = std::dynamic_pointer_cast<
											kernel::Button>(
												widget.lock()))
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
							}; !isHover())
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
	if (m_buttons.contains(buttonID))
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
#endif