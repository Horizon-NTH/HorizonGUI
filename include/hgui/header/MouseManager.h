#pragma once

#include "Coordinate.hpp"
#include "Define.h"

namespace hgui
{
	class Timer;

	typedef std::pair<buttons, actions> MouseAction;
	typedef std::tuple<inputs, buttons, actions> MouseCombinationAction;

	bool operator==(const MouseAction& lhs, const MouseAction& rhs);
	bool operator==(const MouseCombinationAction& lhs, const MouseCombinationAction& rhs);
	bool operator==(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& lhs, const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& rhs);

	class MouseManager
	{
		friend class Renderer;
		friend class WindowManager;

	public:
		MouseManager() = delete;
		~MouseManager() = delete;
		MouseManager(const MouseManager& mouseManager) = delete;
		MouseManager(MouseManager&& mouseManager) = delete;

		MouseManager& operator=(const MouseManager& mouseManager) = delete;
		MouseManager& operator=(MouseManager&& mouseManager) = delete;

		static void bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action, const std::function<void()>& function);
		[[nodiscard]] static bool is_bind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);
		static void unbind(const std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>& action);

		static void bind_click_callback(const std::variant<std::function<void()>, std::function<void(buttons, actions)>>& function);
		static void bind_scroll_callback(const std::variant<std::function<void()>, std::function<void(double, double)>>& function);

		[[nodiscard]] static kernel::Point<HGUI_PRECISION> get_position();

	private:
		static void process();

		static void scroll(GLFWwindow* window, double xOffset, double yOffset);
		static void input(GLFWwindow* window, int button, int action, int mods);

		[[nodiscard]] static bool is_mouse_in_sector(const point& mousePosition, const point& sectorPosition, const size& sectorSize);
		[[nodiscard]] static bool is_action_verified(const std::pair<std::pair<buttons, actions>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>& input);

		static inline std::variant<std::function<void()>, std::function<void(buttons, actions)>> m_clickCallback;
		static inline std::variant<std::function<void()>, std::function<void(double, double)>> m_scrollCallback;
		static inline std::map<std::variant<inputs, std::pair<buttons, actions>, std::tuple<inputs, buttons, actions>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>> m_inputs;

		friend void kernel::resources_cleaner();
	};
}
