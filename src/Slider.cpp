#include "../include/hgui/header/Slider.h"
#include "../include/hgui/header/StraightLine.h"
#include "../include/hgui/header/Circle.h"

hgui::kernel::Slider::Slider(const Ranges& range, const size& size, const point& position, const std::tuple<color, color, color>& colors, Function function) :
	Widget(nullptr, size, position),
	m_range(range),
	m_slider(0.f),
	m_function(std::move(function)),
	m_colors(colors)
{
	m_range.sort();
	set_points();
	set_value(m_range.min);
}

void hgui::kernel::Slider::draw() const
{
	const auto activeBar = std::make_shared<shape::StraightLine>(m_points.first, m_slider, std::get<2>(m_colors), m_size.height / 4.f);
	const auto inactiveBar = std::make_shared<shape::StraightLine>(m_slider, m_points.second, std::get<1>(m_colors), m_size.height / 4.f);
	const auto slider = std::make_shared<shape::Circle>(m_slider, m_size.height / 2.f, std::get<0>(m_colors), true, 0.f);
	const auto drawerPosition = m_position - point(m_size.height / 2.f),
			drawerSize = m_size + point(m_size.height);
	activeBar->draw(drawerPosition, drawerSize);
	inactiveBar->draw(drawerPosition, drawerSize);
	slider->draw(drawerPosition, drawerSize);
}

bool hgui::kernel::Slider::is_inside(const point& point) const
{
	if (!point::is_in_rectangle(m_position, hgui::point(m_position.x + m_size.width, m_position.y), hgui::point(m_position.x, m_position.y + m_size.height), point))
		return false;
	const HGUI_PRECISION a = m_points.second.y - m_points.first.y;
	const HGUI_PRECISION b = m_points.first.x - m_points.second.x;
	const HGUI_PRECISION c = m_points.second.x * m_points.first.y - m_points.first.x * m_points.second.y;
	const bool nearPoint = point::distance(m_slider, point) <= m_size.height / 2.f || point::distance(m_points.second, point) <= m_size.height / 8.f ||
	                       point::distance(m_points.first, point) <= m_size.height / 8.f;
	if (std::abs(a) < 1e-6f)
	{
		return nearPoint || (point.x >= std::min(m_points.second.x, m_points.first.x) &&
		                     point.x <= std::max(m_points.second.x, m_points.first.x) &&
		                     std::abs(m_points.first.y - point.y) <= m_size.height / 8.f);
	}
	if (std::abs(b) < 1e-6f)
	{
		return nearPoint || (point.y >= std::min(m_points.second.y, m_points.first.y) &&
		                     point.y <= std::max(m_points.second.y, m_points.first.y) &&
		                     std::abs(m_points.first.x - point.x) <= m_size.height / 8.f);
	}
	return nearPoint ||
	       (std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b) <= m_size.height / 8.f &&
	        point.x >= std::min(m_points.second.x, m_points.first.x) &&
	        point.x <= std::max(m_points.second.x, m_points.first.x) &&
	        point.y >= std::min(m_points.second.y, m_points.first.y) &&
	        point.y <= std::max(m_points.second.y, m_points.first.y));
}

HGUI_PRECISION hgui::kernel::Slider::get_value() const
{
	return m_range.round(m_range.min + point::distance(m_points.first, m_slider) / point::distance(m_points.first, m_points.second) * (m_range.max - m_range.min));
}

const hgui::kernel::Ranges& hgui::kernel::Slider::get_range() const
{
	return m_range;
}

const hgui::point& hgui::kernel::Slider::get_slider_position() const
{
	return m_slider;
}

const hgui::kernel::Slider::Function& hgui::kernel::Slider::get_function() const
{
	return m_function;
}

const std::tuple<hgui::color, hgui::color, hgui::color>& hgui::kernel::Slider::get_colors() const
{
	return m_colors;
}

void hgui::kernel::Slider::set_position(const point& newPosition)
{
	const HGUI_PRECISION value = get_value();
	Widget::set_position(newPosition);
	set_points();
	set_value(value);
}

void hgui::kernel::Slider::set_size(const size& newSize)
{
	const HGUI_PRECISION value = get_value();
	Widget::set_size(newSize);
	set_points();
	set_value(value);
}

void hgui::kernel::Slider::set_value(HGUI_PRECISION newValue)
{
	newValue = m_range.round(std::clamp(newValue, m_range.min, m_range.max));
	const HGUI_PRECISION offset = (newValue - m_range.min) / (m_range.max - m_range.min) * point::distance(m_points.first, m_points.second);
	point direction = m_points.second - m_points.first;
	direction = point::normalize(direction);
	m_slider = clamp(m_points.first + offset * direction);
}

void hgui::kernel::Slider::set_range(const Ranges& newRange)
{
	m_range = newRange;
	m_range.sort();
}

void hgui::kernel::Slider::set_slider_position(point newPosition)
{
	const point AB = m_points.second - m_points.first,
			AP = newPosition - m_points.first;
	if (const HGUI_PRECISION projection = point::dot(AP, AB) / point::dot(AB, AB); projection < 0)
	{
		newPosition = m_points.first;
	}
	else if (projection > 1)
	{
		newPosition = m_points.second;
	}
	else
	{
		newPosition = m_points.first + projection * AB;
	}
	if (const auto function = std::get_if<std::function<void()>>(&m_function))
	{
		m_slider = clamp(newPosition);
		if (*function)
		{
			(*function)();
		}
	}
	else if (const auto functionWithParameter = std::get_if<std::function<void(HGUI_PRECISION, HGUI_PRECISION, std::shared_ptr<Slider>)>>(&m_function))
	{
		const HGUI_PRECISION pastValue = get_value();
		m_slider = clamp(newPosition);
		if (*functionWithParameter)
		{
			(*functionWithParameter)(get_value(), pastValue, std::dynamic_pointer_cast<Slider>(shared_from_this()));
		}
	}
}

void hgui::kernel::Slider::set_function(const Function& newFunction)
{
	m_function = newFunction;
}

void hgui::kernel::Slider::set_colors(const std::tuple<color, color, color>& newColors)
{
	m_colors = newColors;
}

hgui::point hgui::kernel::Slider::clamp(const point& value) const
{
	if (m_range.step)
	{
		point direction = m_points.second - m_points.first;
		direction = point::normalize(direction);
		const HGUI_PRECISION size = point::distance(m_points.first, m_points.second),
				offset = size / static_cast<float>(m_range.step);
		point actualPoint = m_points.first,
				minPoint = actualPoint;
		HGUI_PRECISION minDistance = point::distance(value, actualPoint);
		while (point::distance(m_points.first, actualPoint) < size)
		{
			actualPoint += offset * direction;
			if (const HGUI_PRECISION distance = point::distance(value, actualPoint); distance < minDistance)
			{
				minDistance = distance;
				minPoint = actualPoint;
			}
		}
		return minPoint;
	}
	return value;
}

void hgui::kernel::Slider::set_points()
{
	m_points = std::make_pair(m_position + point(m_size.height / 8.f, m_size.height / 2.f),
		m_position + point(m_size.width - m_size.height / 8.f, m_size.height / 2.f));
}

HGUI_PRECISION hgui::kernel::Ranges::round(const HGUI_PRECISION value) const
{
	const auto factor = static_cast<HGUI_PRECISION>(std::pow(10, precision));
	return std::round(value * factor) / factor;
}

void hgui::kernel::Ranges::sort()
{
	min = std::min(min, max);
	max = std::max(min, max);
}
