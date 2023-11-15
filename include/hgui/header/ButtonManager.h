#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Font.h"
#include "Button.h"
#include "TagManager.h"
#include "ShaderManager.h"
#include "LabelManager.h"
#include "CursorManager.h"
#include "TaskManager.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class ButtonManager
	{
	public:
		ButtonManager() = delete;
		~ButtonManager() = delete;
		ButtonManager(const ButtonManager& bufferManager) = delete;
		ButtonManager(ButtonManager&& bufferManager) = delete;

		ButtonManager& operator=(const ButtonManager& bufferManager) = delete;
		ButtonManager& operator=(ButtonManager&& bufferManager) = delete;

		[[nodiscard]] static std::shared_ptr<hgui::kernel::Button> create(const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture = nullptr, const color& color = HGUI_COLOR_WHITE, float borderRadius = 0,const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, const hgui::color& textColor = HGUI_COLOR_BLACK, float angularRotation = 0.0f);

	private:
		static std::shared_ptr<kernel::Shader> m_shader;
		static std::shared_ptr<kernel::Cursor> m_cursor;

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

		static const std::shared_ptr<hgui::kernel::Button>& create(const std::string& buttonID, const std::function<void()>& function,
		                                                           const size& size, const point& position,
		                                                           const std::shared_ptr<kernel::Texture>& texture = nullptr,
		                                                           const color& color = HGUI_COLOR_WHITE, float borderRadius = 0,
		                                                           const std::string& text = "",
		                                                           const std::shared_ptr<kernel::Font>& font = nullptr,
		                                                           const hgui::color& textColor = HGUI_COLOR_BLACK,
		                                                           float angularRotation = 0.0f);
		[[nodiscard]] static const std::shared_ptr<kernel::Button>& get(const std::string& buttonID);
		static void destroy(const std::initializer_list<std::string>& buttonsID = {});

	private:
		static std::map<std::string, std::shared_ptr<kernel::Button>> m_buttons;

		friend void kernel::resources_cleaner();
	};
#endif
}
