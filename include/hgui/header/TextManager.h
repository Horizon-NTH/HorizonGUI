#pragma once

#include "Include.h"
#include "Define.h"
#include "TextArea.h"
#include "WidgetManager.h"
#include "Font.h"
#include "ResourceManager.h"
#include "Tools.h"

namespace hgui
{
	namespace kernel
	{
		class TextArea;
		void resources_cleaner();
	}

	class TextManager
	{
	public:
		static const std::shared_ptr<kernel::TextArea>& create(const std::string& textAreaName, const std::string& text, glm::vec2 position, const std::shared_ptr<kernel::Font>& font, std::tuple<unsigned int, glm::vec3, float> textOptions = { 12u, glm::vec3(1.0), 1.0f });
		static const std::shared_ptr<kernel::TextArea>& get(const std::string& textAreaName);
		static void delete_textArea(std::initializer_list<std::string> textAreasNames = {});

	private:
		TextManager();

		static std::map<std::string, std::shared_ptr<kernel::TextArea>> m_textAreas;

		friend void kernel::resources_cleaner();
	};
}
