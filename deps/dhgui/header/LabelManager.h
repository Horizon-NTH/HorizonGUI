#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "TagManager.h"
#include "ShaderManager.h"
#include "Font.h"
#include "Label.h"

namespace hgui
{
	class LabelManager
	{
	public:
		static std::shared_ptr<kernel::Label> create(const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, float>& textOptions = { 12u, HGUI_COLOR_WHITE, 1.0f });

	private:
		LabelManager() = delete;

		static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}
