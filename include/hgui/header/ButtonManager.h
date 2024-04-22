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

#if defined(HGUI_DYNAMIC)
	class ButtonManager
	{
	public:
		ButtonManager() = delete;
		~ButtonManager() = delete;
		ButtonManager(const ButtonManager& buttonManager) = delete;
		ButtonManager(ButtonManager&& buttonManager) = delete;

		ButtonManager& operator=(const ButtonManager& buttonManager) = delete;
		ButtonManager& operator=(ButtonManager&& buttonManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Button> create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture = nullptr, const std::variant<color, std::tuple<color, color, color>>& colors = HGUI_COLOR_WHITE, float borderRadius = 100.f, bool blurrOnHover = true, const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, const color& textColor = HGUI_COLOR_BLACK, HGUI_PRECISION rotation = 0.0f);

	private:
		static inline std::shared_ptr<kernel::Shader> m_shader = {};

		friend void kernel::resources_cleaner();
	};
#elif defined(HGUI_STATIC)
	class ButtonManager
	{
	public:
		ButtonManager() = delete;
		~ButtonManager() = delete;
		ButtonManager(const ButtonManager& bufferManager) = delete;
		ButtonManager(ButtonManager&& bufferManager) = delete;

		ButtonManager& operator=(const ButtonManager& bufferManager) = delete;
		ButtonManager& operator=(ButtonManager&& bufferManager) = delete;

		static const std::shared_ptr<hgui::kernel::Button>& create(const std::string& buttonID, const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture = nullptr, const std::variant<std::tuple<color, color, color>, color>& colors = HGUI_COLOR_WHITE, float borderRadius = 100.f, bool blurrOnHover = true, const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, const color& textColor = HGUI_COLOR_BLACK, HGUI_PRECISION rotation = 0.0f);
		[[nodiscard]] static const std::shared_ptr<kernel::Button>& get(const std::string& buttonID);
		static void destroy(const std::initializer_list<std::string>& buttonsID = {});

	private:
		static std::map<std::string, std::shared_ptr<kernel::Button>> m_buttons;

		friend void kernel::resources_cleaner();
	};
#endif
}
