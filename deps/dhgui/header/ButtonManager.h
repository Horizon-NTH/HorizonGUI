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
#include "TaskManager.h"

namespace hgui
{
	class ButtonManager
	{
	public:
		static std::shared_ptr<hgui::kernel::Button> create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture = nullptr, const color& color = HGUI_COLOR_WHITE, float borderRadius = 0,const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, const hgui::color& textColor = HGUI_COLOR_BLACK, float angularRotation = 0.0f);

	private:
		ButtonManager() = delete;

		static std::shared_ptr<kernel::Shader> m_shader;
		static std::shared_ptr<kernel::Cursor> m_cursor;

		friend void kernel::resources_cleaner();
	};
}
