#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Shader;
		class Canvas;
	}

#if defined(HGUI_DYNAMIC)
	class CanvasManager
	{
	public:
		CanvasManager() = delete;
		~CanvasManager() = delete;
		CanvasManager(const CanvasManager& canvasManager) = delete;
		CanvasManager(CanvasManager&& canvasManager) = delete;

		CanvasManager& operator=(const CanvasManager& canvasManager) = delete;
		CanvasManager& operator=(CanvasManager&& canvasManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Canvas> create(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, HGUI_PRECISION rotation = 0.0f);

	private:
		static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
#elif defined(HGUI_STATIC)
	class CanvasManager
	{
	public:
		CanvasManager() = delete;
		~CanvasManager() = delete;
		CanvasManager(const CanvasManager& bufferManager) = delete;
		CanvasManager(CanvasManager&& bufferManager) = delete;

		CanvasManager& operator=(const CanvasManager& bufferManager) = delete;
		CanvasManager& operator=(CanvasManager&& bufferManager) = delete;

		static const std::shared_ptr<kernel::Canvas>& create(const std::string& canvasID, const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color = HGUI_COLOR_WHITE, HGUI_PRECISION angularRotation = 0.0f);
		[[nodiscard]] static const std::shared_ptr<kernel::Canvas>& get(const std::string& canvasID);
		static void destroy(const std::initializer_list<std::string>& canvasID);

	private:
		static std::map<std::string, std::shared_ptr<kernel::Canvas>> m_canvas;

		friend void kernel::resources_cleaner();
	};
#endif
}
