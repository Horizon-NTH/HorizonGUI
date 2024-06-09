#pragma once

#include "Coordinate.hpp"
#include "Widget.h"

namespace hgui
{
	namespace kernel
	{
		class Font;
		class Cursor;
		class Shader;
		class TextInput;
	}

	class TextInputManager
	{
	public:
		TextInputManager() = delete;
		~TextInputManager() = delete;
		TextInputManager(const TextInputManager& textInputManager) = delete;
		TextInputManager(TextInputManager&& textInputManager) = delete;

		TextInputManager& operator=(const TextInputManager& textInputManager) = delete;
		TextInputManager& operator=(TextInputManager&& textInputManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::TextInput> create(const size& size, const point& position, const std::pair<std::shared_ptr<kernel::Font>, color>& text, const std::pair<color, color>& colors = {HGUI_COLOR_WHITE, color("#097fe0")}, const std::pair<std::string, color>& placeHolder = {"placeholder", color("#424242")}, const std::pair<color, std::chrono::milliseconds>& caret = {HGUI_COLOR_BLACK, std::chrono::milliseconds(500)}, const std::tuple<std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>, std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>, std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>>& onChanges = {}, unsigned sizeLimit = 0u, const std::map<keys, std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>>& onActions = {}, HGUI_PRECISION cornerRadius = 100.f, unsigned borderWidth = 5.f);

	private:
		static inline std::shared_ptr<kernel::Shader> m_shader;
		static inline std::map<std::weak_ptr<kernel::TextInput>, std::map<keys, std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>>, kernel::WeakPTRComparator<kernel::TextInput>> m_actions;

		friend void kernel::resources_cleaner();
	};
}

