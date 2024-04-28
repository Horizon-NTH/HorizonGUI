#include "../include/hgui/header/LabelManager.h"
#include "../include/hgui/header/Label.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/GLSL.h"

std::shared_ptr<hgui::kernel::Label> hgui::LabelManager::create(const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, bool align, const std::tuple<unsigned int, color, HGUI_PRECISION>& textOptions, const HGUI_PRECISION rotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_LABEL, HGUI_GLSL_FRAGMENT_LABEL);
	}
	auto widget = std::make_shared<kernel::Label>(text,
		m_shader, position, font, std::get<0>(textOptions),
		std::get<1>(textOptions), align, std::get<2>(textOptions), rotation);
	return widget;
}
