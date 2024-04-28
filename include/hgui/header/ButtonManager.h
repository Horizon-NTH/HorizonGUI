#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Font;
		class Texture;
		class Cursor;
		class Shader;
		class Button;
	}

	class ButtonManager
	{
	public:
		ButtonManager() = delete;
		~ButtonManager() = delete;
		ButtonManager(const ButtonManager& buttonManager) = delete;
		ButtonManager(ButtonManager&& buttonManager) = delete;

		ButtonManager& operator=(const ButtonManager& buttonManager) = delete;
		ButtonManager& operator=(ButtonManager&& buttonManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Button> create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture = nullptr, const std::variant<color, std::tuple<color, color, color>>& colors = HGUI_COLOR_WHITE, float borderRadius = 100.f, bool blurrOnHover = true, const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, const color& textColor = HGUI_COLOR_BLACK);

	private:
		static inline std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}
