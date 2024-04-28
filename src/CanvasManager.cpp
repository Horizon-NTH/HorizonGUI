#include "../include/hgui/header/CanvasManager.h"
#include "../include/hgui/header/Canvas.h"
#include "../include/hgui/header/TagManager.h"
#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/GLSL.h"

std::shared_ptr<hgui::kernel::Canvas> hgui::CanvasManager::create(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_CANVAS, HGUI_GLSL_FRAGMENT_CANVAS);
	}
	auto widget = std::make_shared<kernel::Canvas>(shader ? shader : m_shader, size, position, color);
	return widget;
}
