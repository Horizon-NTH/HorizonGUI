#pragma once

#include "Include.h"
#include "Define.h"
#include "Widget.h"
#include "Timer.h"
#include "Window.h"

namespace hgui
{
	typedef std::pair<buttons, actions> MouseAction;
	bool operator==(const MouseAction& lhs, const MouseAction& rhs);
	typedef std::tuple<inputs, buttons, actions> MouseCombinationAction;
	bool operator==(const MouseCombinationAction& lhs, const MouseCombinationAction& rhs);

	class MouseManager
	{
		friend class Renderer;
		friend class WindowManager;

	public:
		static void bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function);
		static void unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);
		static void bind_clickcallback(const std::variant<std::function<void()>, std::function<void(buttons, actions)>>& function);
		static void bind_scrollcallback(const std::variant<std::function<void()>, std::function<void(double, double)>>& function);

		static dvec2 get_position();

	private:
		MouseManager() = delete;

		static void process();
		static void scroll(GLFWwindow* window, double xOffset, double yOffset);
		static bool is_mouse_in_sector(const std::pair<double, double>& mousePosition, const point& sectorPosition, const size& sectorSize);
		static bool is_action_verified(const std::pair<std::pair<buttons, actions>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>& input);
		static void input(GLFWwindow* window, int button, int action, int mods);

		static std::variant<std::function<void()>, std::function<void(buttons, actions)>> m_clickCallback;
		static std::variant<std::function<void()>, std::function<void(double, double)>> m_scrollCallback;
		static std::map<std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>> m_inputs;

		friend void kernel::resources_cleaner();
	};
}
