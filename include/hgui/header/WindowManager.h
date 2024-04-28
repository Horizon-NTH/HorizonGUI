#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Image;
		class Monitor;
	}

	typedef std::pair<options, bool> WindowOption;

	class WindowManager
	{
	public:
		WindowManager() = delete;
		~WindowManager() = delete;
		WindowManager(const WindowManager& windowManager) = delete;
		WindowManager(WindowManager&& windowManager) = delete;

		WindowManager& operator=(const WindowManager& windowManager) = delete;
		WindowManager& operator=(WindowManager&& windowManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Window> create(const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon = nullptr, const std::shared_ptr<kernel::Monitor>& monitor = nullptr, const std::map<options, bool>& options = {});
	};
}
