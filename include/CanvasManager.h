#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Shader;
		class Canvas;
	}

	class CanvasManager
	{
	public:
		CanvasManager() = delete;
		~CanvasManager() = delete;
		CanvasManager(const CanvasManager& canvasManager) = delete;
		CanvasManager(CanvasManager&& canvasManager) = delete;

		CanvasManager& operator=(const CanvasManager& canvasManager) = delete;
		CanvasManager& operator=(CanvasManager&& canvasManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Canvas> create(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE);

	private:
		static inline std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}
