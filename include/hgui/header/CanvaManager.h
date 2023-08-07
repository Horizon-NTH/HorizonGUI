#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Canva.h"
#include "TagManager.h"

namespace hgui
{
	namespace kernel
	{
		class Canva;
	}

	class CanvaManager
	{
	public:
		static const std::shared_ptr<kernel::Canva>& create(const std::string& canvaName, const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Canva>& get(const std::string& canvaName);
		static void delete_canva(const std::initializer_list<std::string>& canvasName);

	private:
		CanvaManager();

		static std::map<std::string, std::shared_ptr<kernel::Canva>> m_canvas;
	};
}