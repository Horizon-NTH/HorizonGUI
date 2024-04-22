#include "../include/hgui/header/ButtonManager.h"
#include "../include/hgui/header/Button.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/LabelManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/CursorManager.h"

#if defined(HGUI_DYNAMIC)
#include "../include/hgui/header/GLSL.h"

std::shared_ptr<hgui::kernel::Button> hgui::ButtonManager::create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const std::variant<color, std::tuple<color, color, color>>& colors, const float borderRadius, const bool blurrOnHover, const std::string& text, const std::shared_ptr<kernel::Font>& font, const hgui::color& textColor, HGUI_PRECISION rotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_BUTTON, HGUI_GLSL_FRAGMENT_BUTTON);
	}
	std::tuple<color, color, color> tuple;
	if (!colors.index())
		tuple = {std::get<color>(colors), std::get<color>(colors), std::get<color>(colors)};
	else
		tuple = std::get<std::tuple<color, color, color>>(colors);
	auto button = std::make_shared<kernel::Button>(function,
		m_shader, size, position, nullptr,
		tuple, rotation, borderRadius / 100.f, blurrOnHover, texture);
	if (font)
	{
		button->set_text(LabelManager::create(text, position, font, TextOption(12u, textColor, 1.0f), rotation));
	}
	std::weak_ptr wwidget = std::static_pointer_cast<kernel::Button>(button->shared_from_this());
	auto cursor = CursorManager::create(cursors::HAND);
	button->bind(inputs::OVER, [wwidget, cursor]
		{
			if (const auto widget = wwidget.lock())
			{
				widget->set_state(state::HOVER);
				CursorManager::use(cursor);
			}
		});
	button->bind(inputs::NOVER, [wwidget, cursor]
		{
			if (const auto widget = wwidget.lock())
			{
				widget->set_state(state::NORMAL);
				TaskManager::program(std::chrono::milliseconds(0), [cursor]()
					{
						if (CursorManager::get_cursor_used() == cursor)
						{
							CursorManager::use(nullptr);
						}
					});
			}
		});
	button->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::REPEAT), [wwidget]()
		{
			if (const auto widget = wwidget.lock())
			{
				widget->set_state(state::PRESS);
			}
		});
	button->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::RELEASE), [wwidget, cursor]()
		{
			if (const auto widget = wwidget.lock())
			{
				widget->press();
				TaskManager::program(std::chrono::milliseconds(0), [cursor]()
					{
						if (CursorManager::get_cursor_used() == cursor)
						{
							CursorManager::use(nullptr);
						}
					});
			}
		});
	return button;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Button>> hgui::ButtonManager::m_buttons;

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::create(const std::string& buttonID, const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const std::variant<std::tuple<color, color, color>, color>& colors, const float borderRadius, const bool blurrOnHover, const std::string& text, const std::shared_ptr<kernel::Font>& font, const color& textColor, const HGUI_PRECISION rotation)
{
	if (!m_buttons.contains(buttonID))
	{
		float cornerAngularRadius = std::min(std::min(size.width, size.height) * 0.5f, borderRadius);
		std::tuple<color, color, color> tuple;
		if (colors.index() == 1)
			tuple = {std::get<color>(colors), std::get<color>(colors), std::get<color>(colors)};
		else
			tuple = std::get<std::tuple<color, color, color>>(colors);
		m_buttons[buttonID] = std::make_shared<kernel::Button>(function,
			ShaderManager::get(HGUI_SHADER_BUTTON), size, position,
			font
			? LabelManager::create(
				"HGUI_BUTTON_TEXT_" + buttonID, text, position, font,
				{12, textColor, 1.0f})
			: nullptr,
			tuple, cornerAngularRadius, cornerAngularRadius, blurrOnHover, texture);
		kernel::Widget::bind(m_buttons[buttonID], inputs::OVER, [buttonID]()
			{
				get(buttonID)->set_state(state::HOVER);
				CursorManager::use(CursorManager::get(HGUI_CURSOR_HAND));
			});
		kernel::Widget::bind(m_buttons[buttonID], inputs::NOVER, [buttonID]()
			{
				get(buttonID)->set_state(state::NORMAL);
				TaskManager::program(std::chrono::milliseconds(0), [&]()
					{
						if (auto isHover = []() -> bool
							{
								for (auto& tag : kernel::Widget::get_active_tag())
								{
									for (auto& widget : kernel::Widget::get_widgets(tag))
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
							CursorManager::use(CursorManager::get(HGUI_CURSOR_ARROW));
						}
					});
			});
		kernel::Widget::bind(m_buttons[buttonID], std::make_tuple(inputs::OVER, buttons::LEFT, actions::REPEAT), [buttonID]()
			{
				get(buttonID)->set_state(state::PRESS);
			});
		kernel::Widget::bind(m_buttons[buttonID], std::make_tuple(inputs::OVER, buttons::LEFT, actions::RELEASE), [buttonID]()
			{
				get(buttonID)->press();
				TaskManager::program(std::chrono::milliseconds(0), [&]()
					{
						if (auto isHover = []() -> bool
							{
								for (auto& tag : kernel::Widget::get_active_tag())
								{
									for (auto& widget : kernel::Widget::get_widgets(tag))
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
							CursorManager::use(CursorManager::get(HGUI_CURSOR_ARROW));
						}
					});
			});
		return m_buttons[buttonID];
	}
	throw std::runtime_error(("THERE IS ALREADY A BUTTON WITH THE ID : " + buttonID).c_str());
}

const std::shared_ptr<hgui::kernel::Button>& hgui::ButtonManager::get(const std::string& buttonID)
{
	if (m_buttons.contains(buttonID))
	{
		return m_buttons[buttonID];
	}
	throw std::runtime_error(("THERE IS NO BUTTON WITH THE ID : " + buttonID).c_str());
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
