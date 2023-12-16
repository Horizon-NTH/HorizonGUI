#include <hgui/header/SliderManager.h>

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Cursor> hgui::SliderManager::m_cursor(nullptr);

std::shared_ptr<hgui::kernel::Slider> hgui::SliderManager::create(const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor, const color& activeBarColor, const color& sliderColor, const Function& function, HGUI_PRECISION angularRotation)
{
	auto widget = std::make_shared<kernel::Slider>(range, inactiveBarColor, activeBarColor, size, position, sliderColor, function, angularRotation);
	std::weak_ptr<kernel::Slider> wwidget = std::static_pointer_cast<kernel::Slider>(widget->shared_from_this());
	Widget::m_widgets[TagManager::get_current_tag()].push_back(wwidget);
	widget->bind(inputs::OVER, [wwidget]()
		{
			if (!m_cursor)
			{
				m_cursor = CursorManager::create(cursors::HAND);
			}
			m_cursor->use();
		});
	widget->bind(inputs::NOVER, [wwidget]()
		{
			m_cursor = nullptr;
		});
	static std::function<void()> move = [&, wwidget]()
		{
			std::pair<double, double> mousePosition;
			glfwGetCursorPos(glfwGetCurrentContext(), &mousePosition.first, &mousePosition.second);
			auto widget = wwidget.lock();
			widget->set_slider_position(point(mousePosition.first, mousePosition.second));
			if (!widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
			{
				widget->bind(std::make_pair(buttons::LEFT, actions::REPEAT), move);
			}
		};
	widget->bind(std::make_tuple(inputs::OVER, buttons::LEFT, actions::PRESS), move);
	widget->bind(std::make_pair(buttons::LEFT, actions::RELEASE), [wwidget]()
		{
			auto widget = wwidget.lock();
			if (widget->is_bind(std::make_pair(buttons::LEFT, actions::REPEAT)))
			{
				widget->unbind(std::make_pair(buttons::LEFT, actions::REPEAT));
			}
		});
	return widget;
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Slider>> hgui::SliderManager::m_sliders;

const std::shared_ptr<hgui::kernel::Slider>& hgui::SliderManager::create(const std::string& sliderID, const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor, const color& activeBarColor, const color& sliderColor, HGUI_PRECISION angularRotation)
{
	if (!m_sliders.contains(sliderID))
	{
		m_sliders[sliderID] = std::make_shared<kernel::Slider>(range, inactiveBarColor, activeBarColor, size, position, sliderColor, angularRotation);
		Widget::m_widgets[TagManager::get_current_tag()].push_back(m_sliders[sliderID]->weak_from_this());
		return m_sliders[sliderID];
	}
	else
	{
		throw std::runtime_error(("THERE IS ALREADY A SLIDER WITH THE ID : " + sliderID).c_str());
	}
}

const std::shared_ptr<hgui::kernel::Slider>& hgui::SliderManager::get(const std::string& sliderID)
{
	if (m_sliders.contains(sliderID))
	{
		return m_sliders[sliderID];
	}
	else
	{
		throw std::runtime_error(("THERE IS NO SLIDERS WITH THE ID : " + sliderID).c_str());
	}
}

void hgui::SliderManager::destroy(const std::initializer_list<std::string>& slidersID)
{
	if (slidersID.size())
	{
		for (const std::string& id : slidersID)
		{
			m_sliders.erase(id);
		}
	}
	else
	{
		m_sliders.clear();
	}
}
#endif