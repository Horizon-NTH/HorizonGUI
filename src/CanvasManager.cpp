#include "../include/hgui/header/CanvasManager.h"
#include "../include/hgui/header/TagManager.h"

#if defined(HGUI_DYNAMIC)
#include "../include/hgui/header/GLSL.h"

std::shared_ptr<hgui::kernel::Shader> hgui::CanvasManager::m_shader(nullptr);

std::shared_ptr<hgui::kernel::Canvas> hgui::CanvasManager::create(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, HGUI_PRECISION angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(HGUI_GLSL_VERTEX_CANVAS, HGUI_GLSL_FRAGMENT_CANVAS);
	}
	auto widget = std::make_shared<kernel::Canvas>(shader ? shader : m_shader, size, position, color, angularRotation);
	return widget;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Canvas>> hgui::CanvasManager::m_canvas;

const std::shared_ptr<hgui::kernel::Canvas>& hgui::CanvasManager::create(const std::string& canvasID, const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, HGUI_PRECISION angularRotation)
{
	if (!m_canvas.contains(canvasID))
	{
		m_canvas[canvasID] = std::make_shared<kernel::Canvas>(shader ? shader : ShaderManager::get(HGUI_SHADER_CANVAS), size, position, color,
			angularRotation);
		return m_canvas[canvasID];
	}
	throw std::runtime_error(("THERE IS ALREADY A CANVAS WITH THE ID : " + canvasID).c_str());
}

const std::shared_ptr<hgui::kernel::Canvas>& hgui::CanvasManager::get(const std::string& canvasID)
{
	if (m_canvas.contains(canvasID))
	{
		return m_canvas[canvasID];
	}
	throw std::runtime_error(("THERE IS NO CANVAS WITH THE ID : " + canvasID).c_str());
}

void hgui::CanvasManager::destroy(const std::initializer_list<std::string>& canvasID)
{
	if (canvasID.size())
	{
		for (const std::string& id : canvasID)
		{
			m_canvas.erase(id);
		}
	}
	else
	{
		m_canvas.clear();
	}
}
#endif
