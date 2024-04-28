#include "../include/hgui/header/TextInputManager.h"
#include "../include/hgui/header/TextInput.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/LabelManager.h"
#include "../include/hgui/header/TaskManager.h"
#include "../include/hgui/header/CursorManager.h"
#include "../include/hgui/header/GLSL.h"
#include "../include/hgui/header/KeyBoardManager.h"
#include "../include/hgui/header/MouseManager.h"

std::shared_ptr<hgui::kernel::TextInput> hgui::TextInputManager::create(const size& size, const point& position, const std::pair<std::shared_ptr<kernel::Font>, color>& text, const std::pair<color, color>& colors, const std::pair<std::string, color>& placeHolder, const std::pair<color, std::chrono::milliseconds>& caret, const std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>& onChange, const std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>& onEnter, const HGUI_PRECISION cornerRadius, const unsigned borderWidth)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_TEXTINPUT, HGUI_GLSL_FRAGMENT_TEXTINPUT);
		const auto moveCaretLeft = []
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					if (!focused->get_caret_position())
						return;
					focused->set_caret_position(focused->get_caret_position() - 1);
				}
			};
		KeyBoardManager::add_bind(KeyBoardAction(keys::LEFT, actions::PRESS), moveCaretLeft);
		KeyBoardManager::add_bind(KeyBoardAction(keys::LEFT, actions::REPEAT), moveCaretLeft);
		const auto moveCaretRight = []
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					focused->set_caret_position(focused->get_caret_position() + 1);
				}
			};
		KeyBoardManager::add_bind(KeyBoardAction(keys::RIGHT, actions::PRESS), moveCaretRight);
		KeyBoardManager::add_bind(KeyBoardAction(keys::RIGHT, actions::REPEAT), moveCaretRight);
		KeyBoardManager::add_bind(KeyBoardAction(keys::ENTER, actions::PRESS), [onEnter]
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					if (const auto functionWithWidgetAsParameter = std::get_if<std::function<void(const std::shared_ptr<kernel::TextInput>&)>>(&onEnter); functionWithWidgetAsParameter && *functionWithWidgetAsParameter)
					{
						(*functionWithWidgetAsParameter)(focused);
					}
					else if (const auto functionWithoutWidgetAsParameter = std::get_if<std::function<void()>>(&onEnter); functionWithoutWidgetAsParameter && *functionWithoutWidgetAsParameter)
					{
						(*functionWithoutWidgetAsParameter)();
					}
				}
			});
		const auto delChar = []
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					focused->delete_char();
				}
			};
		KeyBoardManager::add_bind(KeyBoardAction(keys::REMOVE, actions::PRESS), delChar);
		KeyBoardManager::add_bind(KeyBoardAction(keys::REMOVE, actions::REPEAT), delChar);
		const auto supprChar = []
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					focused->suppress_char();
				}
			};
		KeyBoardManager::add_bind(KeyBoardAction(keys::BACKSPACE, actions::PRESS), supprChar);
		KeyBoardManager::add_bind(KeyBoardAction(keys::BACKSPACE, actions::REPEAT), supprChar);
		const auto switchLeft = []
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					focused->set_caret_position(0u);
				}
			};
		KeyBoardManager::add_bind(KeyBoardCombinationAction({keys::LEFT_CONTROL, keys::LEFT}, actions::PRESS), switchLeft);
		KeyBoardManager::add_bind(KeyBoardCombinationAction({keys::RIGHT_CONTROL, keys::LEFT}, actions::PRESS), switchLeft);
		const auto switchRight = []
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					focused->set_caret_position(static_cast<unsigned>(focused->get_value().size()));
				}
			};
		KeyBoardManager::add_bind(KeyBoardCombinationAction({keys::LEFT_CONTROL, keys::RIGHT}, actions::PRESS), switchRight);
		KeyBoardManager::add_bind(KeyBoardCombinationAction({keys::RIGHT_CONTROL, keys::RIGHT}, actions::PRESS), switchRight);
		KeyBoardManager::add_bind(KeyBoardAction(keys::ESCAPE, actions::PRESS), []
			{
				if (const auto focused = kernel::TextInput::m_focused.lock())
				{
					if (focused->is_focused())
					{
						focused->unfocus();
					}
				}
			});
	}
	if (!text.first)
	{
		throw std::runtime_error("TEXT INPUT REQUIRES A FONT");
	}
	auto textInput = std::make_shared<kernel::TextInput>(m_shader, size, position, nullptr, colors, placeHolder, caret, onChange, cornerRadius / 100.f, borderWidth);
	textInput->set_label(LabelManager::create("", position, text.first, true, TextOption(12u, text.second, 1.0f)));
	std::weak_ptr wwidget = std::static_pointer_cast<kernel::TextInput>(textInput->shared_from_this());
	auto cursor = CursorManager::create(cursors::IBEAM);
	textInput->bind(inputs::OVER, [cursor]
		{
			CursorManager::use(cursor);
		});
	textInput->bind(inputs::NOVER, [cursor]
		{
			TaskManager::program(std::chrono::milliseconds(0), [cursor]
				{
					if (CursorManager::get_cursor_used() == cursor)
					{
						CursorManager::use(nullptr);
					}
				});
		});
	textInput->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::PRESS), [wwidget]
		{
			if (const auto widget = wwidget.lock())
			{
				if (!widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					if (!widget->is_focused())
					{
						widget->focus();
					}
					widget->set_caret_position(widget->get_caret_position_from_point(MouseManager::get_position()));
					widget->bind(std::make_pair(buttons::LEFT, actions::REPEAT), [wwidget]
						{
							if (const auto widget = wwidget.lock())
							{
								std::pair<double, double> mousePosition;
								glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
							}
						});
				}
			}
		});
	textInput->bind(std::make_tuple(inputs::NOVER, buttons::LEFT, actions::PRESS), [wwidget]
		{
			if (const auto widget = wwidget.lock())
			{
				if (widget->is_focused())
				{
					widget->unfocus();
				}
			}
		});
	textInput->bind(std::make_pair(buttons::LEFT, actions::RELEASE), [wwidget, cursor]
		{
			if (const auto widget = wwidget.lock())
			{
				if (widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
				{
					widget->unbind(std::make_pair(buttons::LEFT, actions::REPEAT));
				}
				TaskManager::program(std::chrono::milliseconds(0), [widget, cursor]
					{
						if (CursorManager::get_cursor_used() == cursor)
						{
							std::pair<double, double> mousePosition;
							glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
							if (widget && !widget->is_inside(point(mousePosition.first, mousePosition.second)))
								CursorManager::use(nullptr);
						}
					});
			}
		});
	return textInput;
}
