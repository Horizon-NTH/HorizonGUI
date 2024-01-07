#pragma once

#include "Include.h"
#include "Define.h"
#include "Maths.hpp"
#include "Window.h"

namespace hgui
{
	typedef std::pair<options, bool> WindowOption;
#if defined(HGUI_DYNAMIC)
	class WindowManager
	{
	public:
		WindowManager() = delete;
		~WindowManager() = delete;
		WindowManager(const WindowManager& windowManager) = delete;
		WindowManager(WindowManager&& windowManager) = delete;

		WindowManager& operator=(const WindowManager& windowManager) = delete;
		WindowManager& operator=(WindowManager&& windowManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Window> create(const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon = nullptr, const std::shared_ptr<kernel::Monitor>& monitor = nullptr, const std::initializer_list<WindowOption>& options = {});
	};
#elif defined(HGUI_STATIC)
	class WindowManager
	{
	public:
		WindowManager() = delete;
		~WindowManager() = delete;
		WindowManager(const WindowManager& bufferManager) = delete;
		WindowManager(WindowManager&& bufferManager) = delete;

		WindowManager& operator=(const WindowManager& bufferManager) = delete;
		WindowManager& operator=(WindowManager&& bufferManager) = delete;

		static const std::shared_ptr<kernel::Window>& create(const std::string& windowID, const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon = nullptr, const std::shared_ptr<kernel::Monitor>& monitor = nullptr, const std::initializer_list<std::pair<options, bool>>& options = {});
		[[nodiscard]] static const std::shared_ptr<kernel::Window>& get(const std::string& windowID);
		static void destroy(const std::initializer_list<std::string>& windowsID = {});

	private:
		static std::map<std::string, std::shared_ptr<kernel::Window>> m_windows;

		friend void kernel::resources_cleaner();
	};
#endif
}
