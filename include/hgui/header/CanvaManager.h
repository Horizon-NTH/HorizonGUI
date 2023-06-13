#pragma once

#include "Include.h"
#include "Canva.h"
#include "WidgetManager.h"

namespace hgui
{
	namespace kernel
	{
		class Canva;
	}

	class CanvaManager
	{
	public:
		static const std::shared_ptr<kernel::Canva>& create(const std::string& canvaName, const std::shared_ptr<kernel::Shader>& shader, glm::vec2 size, glm::vec2 position, glm::vec3 color = glm::vec3(0.0), float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Canva>& get(const std::string& canvaName);
		static void delete_canva(std::initializer_list<std::string> canvasName);

	private:
		CanvaManager();

		static std::map<std::string, std::shared_ptr<kernel::Canva>> m_canvas;
	};
}