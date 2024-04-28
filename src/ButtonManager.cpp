#include "../include/hgui/header/ButtonManager.h"
#include "../include/hgui/header/Button.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/LabelManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/CursorManager.h"
#include "../include/hgui/header/GLSL.h"

std::shared_ptr<hgui::kernel::Button> hgui::ButtonManager::create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture, const std::variant<color, std::tuple<color, color, color>>& colors, const float borderRadius, const bool blurrOnHover, const std::string& text, const std::shared_ptr<kernel::Font>& font, const hgui::color& textColor)
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
		tuple, borderRadius / 100.f, blurrOnHover, texture);
	if (font)
	{
		button->set_label(LabelManager::create(text, position, font, false, TextOption(12u, textColor, 1.0f)));
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
				TaskManager::program(std::chrono::milliseconds(0), [cursor]
					{
						if (CursorManager::get_cursor_used() == cursor)
						{
							CursorManager::use(nullptr);
						}
					});
			}
		});
	button->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::REPEAT), [wwidget]
		{
			if (const auto widget = wwidget.lock())
			{
				widget->set_state(state::PRESS);
			}
		});
	button->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::RELEASE), [wwidget, cursor]
		{
			if (const auto widget = wwidget.lock())
			{
				widget->press();
				TaskManager::program(std::chrono::milliseconds(0), [cursor]
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
