#include <hgui/header/CanvasManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Shader> hgui::CanvasManager::m_shader(nullptr);

std::shared_ptr<hgui::kernel::Canvas> hgui::CanvasManager::create(const std::shared_ptr<kernel::Shader>& shader,
                                                                  const size& size, const point& position,
                                                                  const color& color, float angularRotation)
{
	if (!m_shader)
	{
		m_shader = ShaderManager::create(
			R"(
				#version 330 core

				layout (location = 0) in vec2 vertex;
				layout (location = 1) in vec3 vertexColor;

				out vec3 color;

				uniform mat4 modelMatrix;
				uniform mat4 projectionMatrix;

				void main()
				{
					gl_Position = projectionMatrix * modelMatrix * vec4(vertex, 0.0, 1.0);
					color = vertexColor;
				}
			)",
			R"(
				#version 330 core

				in vec3 color;

				out vec4 fragmentColor;

				void main()
				{
					fragmentColor = vec4(color, 1.0);
				}
			)"
		);
	}
	auto widget = std::make_shared<kernel::Canvas>(shader ?
		                                               shader :
		                                               m_shader, size, position, color, angularRotation);
	Widget::m_widgets[TagManager::get_current_tag()].push_back(widget->weak_from_this());
	return widget;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Canvas>> hgui::CanvasManager::m_canvas;

const std::shared_ptr<hgui::kernel::Canvas>& hgui::CanvasManager::create(const std::string& canvasID,
                                                                         const std::shared_ptr<kernel::Shader>& shader, const size& size,
                                                                         const point& position, const color& color, float angularRotation)
{
	if (!m_canvas.contains(canvasID))
	{
		m_canvas[canvasID] = std::make_shared<kernel::Canvas>(shader ?
			                                                      shader :
			                                                      ShaderManager::get(HGUI_SHADER_CANVAS), size, position, color,
		                                                      angularRotation);
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_canvas[canvasID]->weak_from_this());
		return m_canvas[canvasID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A TEXT AREA WITH THE ID : " + canvasID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Canvas>& hgui::CanvasManager::get(const std::string& canvasID)
{
	if (m_canvas.contains(canvasID))
	{
		return m_canvas[canvasID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO CANVAS WITH THE ID : " + canvasID).c_str());
	}
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
