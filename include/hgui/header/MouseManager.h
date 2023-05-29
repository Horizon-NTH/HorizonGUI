#pragma once

#include "Include.h"
#include "WindowManager.h"
#include "Window.h"
#include "Timer.h"
#include "Tools.h"

namespace hgui
{
	namespace input
	{
		enum MouseButton
		{
			LEFT = 0,
			RIGHT = 1,
			MIDDLE = 2,
			BUTTON_3 = 3,
			BUTTON_4 = 4,
			BUTTON_5 = 5,
			BUTTON_6 = 6,
			BUTTON_7 = 7,
			BUTTON_8 = 8,
		};

		enum MouseInput
		{
			OVER,
			NOVER,
			MOTION,
			SCROLL,
			SCROLL_UP,
			SCROLL_DOWN,
		};

		enum Action
		{
			PRESS = 1,
			REPEAT = 2,
			RELEASE = 0
		};
	}
	namespace kernel
	{
		void resources_cleaner();
	}

	typedef std::pair<input::MouseButton, input::Action> MouseAction;
	typedef std::tuple<input::MouseInput, input::MouseButton, input::Action> MouseCombinationAction;

	class MouseManager
	{
		friend class RenderManager;
		friend class WindowManager;
		friend class WidgetManager;

	public:
		static void bind(std::variant<hgui::input::MouseInput, std::pair<hgui::input::MouseButton, hgui::input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>> action, std::function<void()> function);
		static void unbind(std::variant<hgui::input::MouseInput, std::pair<hgui::input::MouseButton, hgui::input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>> action);

		static glm::vec2 get_position();
	private:
		MouseManager();

		static void process();
		static void scroll(GLFWwindow* window, double xOffset, double yOffset);
		static bool is_mouse_in_sector(std::pair<double, double> mousePosition, glm::vec2 sectorPosition, glm::vec2 sectorSize);
		static bool is_action_verified(const std::pair<std::pair<input::MouseButton, input::Action>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>& input);

		static std::map<std::variant<input::MouseInput, std::pair<input::MouseButton, input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>> m_inputs;
	
		friend void kernel::resources_cleaner();
	};
}