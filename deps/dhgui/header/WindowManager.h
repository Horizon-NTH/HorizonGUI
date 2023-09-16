#pragma once

#include "Include.h"
#include "Define.h"
#include "Maths.hpp"
#include "Window.h"
#include "MouseManager.h"
#include "KeyBoardManager.h"
#include "Function.h"

namespace hgui
{
	typedef std::pair<options, bool> WindowOption;

	class WindowManager
	{
	public:
		static std::shared_ptr<kernel::Window> create(const std::string& windowName, const size& size, const point& position, const std::shared_ptr<kernel::Image>& icon = nullptr, const std::shared_ptr<kernel::Monitor>& monitor = nullptr, const std::initializer_list<std::pair<options, bool>>& options = {});

	private:
		WindowManager() = delete;
	};
}