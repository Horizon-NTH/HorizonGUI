#include <hgui/header/CanvaManager.h>

std::map<std::string, std::shared_ptr<hgui::kernel::Canva>> hgui::CanvaManager::m_canvas;

const std::shared_ptr<hgui::kernel::Canva>& hgui::CanvaManager::create(const std::string& canvaName, const std::shared_ptr<kernel::Shader>& shader, const size& size, const point& position, const color& color, float angularRotation)
{
	if (m_canvas.find(canvaName) == m_canvas.end())
	{
		m_canvas[canvaName] = std::make_shared<kernel::Canva>(shader, size, position, color, angularRotation);
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_canvas[canvaName]);
		return m_canvas[canvaName];
	}
	else
	{
		throw std::exception(("THERE IS ALREADY A TEXT AREA WITH THE NAME : " + canvaName).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Canva>& hgui::CanvaManager::get(const std::string& canvaName)
{
	if (m_canvas.find(canvaName) != m_canvas.end())
	{
		return m_canvas[canvaName];
	}
	else
	{
		throw std::exception(("THERE IS NO CANVA WITH THE NAME : " + canvaName).c_str());
	}
}

void hgui::CanvaManager::delete_canva(const std::initializer_list<std::string>& canvasName)
{
	if (canvasName.size())
	{
		for (const std::string& canva : canvasName)
		{
			Widget::delete_widget(m_canvas[canva]);
			m_canvas.erase(canva);
		}
	}
	else
	{
		for (auto& canva : m_canvas)
		{
			Widget::delete_widget(canva.second);
		}
		m_canvas.clear();
	}
}
