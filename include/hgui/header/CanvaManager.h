#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Canva.h"
#include "ResourceManager.h"
#include "TagManager.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	class CanvaManager
	{
	public:
		static const std::shared_ptr<kernel::Canva>& create(const std::string& canvaID, const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Canva>& get(const std::string& canvaID);
		static void destroy(const std::initializer_list<std::string>& canvasID);

	private:
		CanvaManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Canva>> m_canvas;
		friend void kernel::resources_cleaner();
	};
}