#include <hgui/header/CanvaManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Shader> hgui::CanvaManager::m_shader(nullptr);

std::shared_ptr<hgui::kernel::Canva> hgui::CanvaManager::create(const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, float angularRotation)
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

				uniform vec2 canvaPosition;
				uniform vec2 canvaSize;

				void main()
				{
					fragmentColor = vec4(color, 1.0);
				}
			)"
		);
	}
	auto widget = std::make_shared<kernel::Canva>(shader ? shader :
		m_shader, size, position, color, angularRotation);
	Widget::m_widgets[TagManager::get_current_tag()].push_back(widget->weak_from_this());
	return widget;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Canva>> hgui::CanvaManager::m_canvas;

const std::shared_ptr<hgui::kernel::Canva>& hgui::CanvaManager::create(const std::string& canvaID, const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, float angularRotation)
{
	if (m_canvas.find(canvaID) == m_canvas.end())
	{
		m_canvas[canvaID] = std::make_shared<kernel::Canva>(shader ? shader :
			ShaderManager::get(HGUI_SHADER_CANVA), size, position, color, angularRotation);
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_canvas[canvaID]->weak_from_this());
		return m_canvas[canvaID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A TEXT AREA WITH THE ID : " + canvaID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Canva>& hgui::CanvaManager::get(const std::string& canvaID)
{
	if (m_canvas.find(canvaID) != m_canvas.end())
	{
		return m_canvas[canvaID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO CANVA WITH THE ID : " + canvaID).c_str());
	}
}

void hgui::CanvaManager::destroy(const std::initializer_list<std::string>& canvasID)
{
	if (canvasID.size())
	{
		for (const std::string& canvaID : canvasID)
		{
			m_canvas.erase(canvaID);
		}
	}
	else
	{
		m_canvas.clear();
	}
}
#endif