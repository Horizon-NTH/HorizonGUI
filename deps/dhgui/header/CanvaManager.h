#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Canva.h"
#include "ShaderManager.h"
#include "TagManager.h"

namespace hgui
{
	class CanvaManager
	{
	public:
		static std::shared_ptr<kernel::Canva> create(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, float angularRotation = 0.0f);

	private:
		CanvaManager() = delete;

		static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}
