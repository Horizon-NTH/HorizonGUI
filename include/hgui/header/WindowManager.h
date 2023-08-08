#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Window.h"
#include "../HorizonGUI.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	typedef std::pair<options, bool> WindowOption;

	class WindowManager
	{
	public:
		static const std::shared_ptr<kernel::Window>& create(const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon = nullptr, const std::shared_ptr<kernel::Monitor>& monitor = nullptr, const std::initializer_list<std::pair<options, bool>>& options = {});
		static const std::shared_ptr<kernel::Window>& get(const std::string& windowName);
		static void delete_windows(const std::initializer_list<std::string>& windowsNames = {});
		static GLFWwindow* get_current_windowPTR();

	private:
		WindowManager();

		static std::map<std::string, std::shared_ptr<kernel::Window>> m_windows;

		friend void kernel::resources_cleaner();
	};
}

