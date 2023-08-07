#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Label.h"
#include "Font.h"
#include "ResourceManager.h"
#include "TagManager.h"

namespace hgui
{
	namespace kernel
	{
		class Label;
		void resources_cleaner();
	}

	class LabelManager
	{
	public:
		static const std::shared_ptr<kernel::Label>& create(const std::string& textAreaName, const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, float>& textOptions = { 12u, HGUI_COLOR_WHITE, 1.0f });
		static const std::shared_ptr<kernel::Label>& get(const std::string& textAreaName);
		static void delete_textArea(const std::initializer_list<std::string>& textAreasNames = {});

	private:
		LabelManager();

		static std::map<std::string, std::shared_ptr<kernel::Label>> m_textAreas;

		friend void kernel::resources_cleaner();
	};
}
