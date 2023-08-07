#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Button.h"
#include "ResourceManager.h"
#include "TagManager.h"

namespace hgui
{
	namespace kernel
	{
		class Button;
		class Font;
		void resources_cleaner();
	}

	class ButtonManager
	{
	public:
		static const std::shared_ptr<hgui::kernel::Button>& create(const std::string& buttonName, const std::function<void()>& function, const size& size, const point& position, const std::shared_ptr<kernel::Texture>& texture = nullptr, const color& color = HGUI_COLOR_WHITE, const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, const std::tuple<unsigned int, hgui::color, float>& textOptions = { 12u, HGUI_COLOR_WHITE, 1.0f }, float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Button>& get(const std::string& buttonName);
		static void delete_button(const std::initializer_list<std::string>& buttonsNames = {});

	private:
		ButtonManager();

		static std::map<std::string, std::shared_ptr<kernel::Button>> m_buttons;

		friend void kernel::resources_cleaner();
	};
}


