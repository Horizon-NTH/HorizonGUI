#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Canvas.h"
#include "ShaderManager.h"
#include "TagManager.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class CanvasManager
	{
	public:
		[[nodiscard]] static std::shared_ptr<kernel::Canvas> create(const std::shared_ptr<kernel::Shader>& shader, const size& size,
		                                              const point& position, const color& color = HGUI_COLOR_WHITE,
		                                              float angularRotation = 0.0f);

	private:
		CanvasManager() = delete;

		static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
#elif defined(HGUI_STATIC)
	class CanvasManager
	{
	public:
		static const std::shared_ptr<kernel::Canvas>& create(const std::string& canvasID, const std::shared_ptr<kernel::Shader>& shader,
		                                                     const size& size, const point& position, const color& color = HGUI_COLOR_WHITE,
		                                                     float angularRotation = 0.0f);
		[[nodiscard]] static const std::shared_ptr<kernel::Canvas>& get(const std::string& canvasID);
		static void destroy(const std::initializer_list<std::string>& canvasID);

	private:
		CanvasManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Canvas>> m_canvas;

		friend void kernel::resources_cleaner();
	};
#endif
}
