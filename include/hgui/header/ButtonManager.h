#pragma once

#include "Include.h"
#include "Define.h"
#include "WidgetManager.h"
#include "Button.h"
#include "ResourceManager.h"
#include "Tools.h"

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
		static const std::shared_ptr<hgui::kernel::Button>& create(const std::string& buttonName, std::function<void()> function, glm::vec2 size, glm::vec2 position, std::shared_ptr<kernel::Texture> texture = nullptr, glm::vec3 color = glm::vec3(1.0f), const std::string& text = "", const std::shared_ptr<kernel::Font>& font = nullptr, std::tuple<unsigned int, glm::vec3, float> textOptions = { 12u, glm::vec3(1.0), 1.0f }, float angularRotation = 0.0f);
		static const std::shared_ptr<kernel::Button>& get(const std::string& buttonName);
		static void delete_button(std::initializer_list<std::string> buttonsNames = {});

	private:
		ButtonManager();

		static std::map<std::string, std::shared_ptr<kernel::Button>> m_buttons;

		friend void kernel::resources_cleaner();
	};
}


