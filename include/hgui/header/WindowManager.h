#pragma once

#include "Include.h"
#include "Window.h"
#include "../HorizonGUI.h"
#include "Tools.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	typedef std::pair<kernel::WindowOptions, bool> WindowOption;

	class WindowManager
	{
	public:
		static const std::shared_ptr<kernel::Window>& create(const std::string& windowName, glm::vec2 size, glm::vec2 position, const std::shared_ptr<kernel::Image>& icon = nullptr, std::initializer_list<std::pair<kernel::WindowOptions, bool>> options = {});
		static const std::shared_ptr<kernel::Window>& get(const std::string& windowName);
		static void delete_windows(std::initializer_list<std::string> windowsNames = {});
		static GLFWwindow* get_current_windowPTR();

	private:
		WindowManager();

		static std::map<std::string, std::shared_ptr<kernel::Window>> m_windows;

		friend void kernel::resources_cleaner();
	};
}

