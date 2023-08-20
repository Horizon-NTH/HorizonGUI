#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Font.h"
#include "Button.h"
#include "TagManager.h"
#include "ShaderManager.h"
#include "LabelManager.h"
#include "CursorManager.h"

namespace hgui
{
	class ButtonManager
	{
	public:
		static const std::shared_ptr<hgui::kernel::Button>& create(const std::string& buttonID, const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture = nullptr, const color& color = HGUI_COLOR_WHITE, const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, const std::tuple<unsigned int, hgui::color, float>& textOptions = { 12u, HGUI_COLOR_WHITE, 1.0f }, float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Button>& get(const std::string& buttonID);
		static void destroy(const std::initializer_list<std::string>& buttonsID = {});

	private:
		ButtonManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Button>> m_buttons;

		friend void kernel::resources_cleaner();
	};
}
