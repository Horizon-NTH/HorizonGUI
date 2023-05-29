#pragma once

#include "Include.h"
#include "Timer.h"
#include "Widget.h"
#include "MouseManager.h"
#include "Tools.h"

namespace hgui
{
	namespace input
	{
		enum MouseButton;
		enum MouseInput;
		enum Action;
	}
	namespace kernel
	{
		void resources_cleaner();
	}

	class WidgetManager
	{
		friend class RenderManager;
		friend class SpriteManager;
		friend class TextManager;
		friend class ButtonManager;
		friend class MouseManager;

	public:
		static std::string create_tag(const std::string& newTag);
		static const std::vector<std::string>& get_tags();
		static const std::string& get_current_tag();
		static void set_current_tag(const std::string& tag);

		static void bind(std::variant<std::string, std::vector<std::string>, std::shared_ptr<kernel::Widget>> widgets, std::variant<input::MouseInput, std::pair<input::MouseButton, input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>> action, std::function<void()> function);
		static void active(std::vector<std::string> tags = {});
		static const std::vector<std::shared_ptr<kernel::Widget>>& get_widgets(const std::string& tag);

	private:
		WidgetManager();

		static void delete_widget(const std::shared_ptr<kernel::Widget>& widget);

		static std::string m_currentTag;
		static std::vector<std::string> m_tags;
		static std::vector<std::string> m_bindedTags;
		static std::map<std::shared_ptr<kernel::Widget>, std::vector<std::pair<std::variant<input::MouseInput, std::pair<input::MouseButton, input::Action>, std::tuple<input::MouseInput, input::MouseButton, input::Action>>, std::pair<std::shared_ptr<Timer>, std::function<void()>>>>> m_binds;
		static std::map<std::string, std::vector<std::shared_ptr<kernel::Widget>>> m_widgets;

		friend void kernel::resources_cleaner();
	};
}

