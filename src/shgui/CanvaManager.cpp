#include <hgui/header/CanvaManager.h>

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
		throw std::exception(("THERE IS ALREADY A TEXT AREA WITH THE ID : " + canvaID).c_str());
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
		throw std::exception(("THERE IS NO CANVA WITH THE ID : " + canvaID).c_str());
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
