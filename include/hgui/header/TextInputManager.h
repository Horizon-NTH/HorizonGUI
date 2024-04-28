#pragma once

#include "Coordinate.hpp"

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

		[[nodiscard]] static std::shared_ptr<kernel::TextInput> create(const size& size, const point& position, const std::pair<std::shared_ptr<kernel::Font>, color>& text, const std::pair<color, color>& colors = {HGUI_COLOR_WHITE, color("#097fe0")}, const std::pair<std::string, color>& placeHolder = {"placeholder", color("#424242")}, const std::pair<color, std::chrono::milliseconds>& caret = {HGUI_COLOR_BLACK, std::chrono::milliseconds(500)}, const std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>& onChange = {}, const std::variant<std::function<void()>, std::function<void(const std::shared_ptr<kernel::TextInput>&)>>& onEnter = {}, HGUI_PRECISION cornerRadius = 100.f, unsigned borderWidth = 5.f);

	private:
		static inline std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}

