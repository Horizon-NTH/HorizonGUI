#include <hgui/header/Slider.h>

hgui::kernel::Slider::Slider(const Ranges& range, const color& inactiveBarColor, const color& activeBarColor, const size& size, const point& position, const color& color, const Function& function, const HGUI_PRECISION angularRotation) :
	Widget(nullptr, size, position, color, angularRotation),
	m_modelMatrix(1.0f),
	m_range(range),
	m_inactiveBarColor(inactiveBarColor),
	m_activeBarColor(activeBarColor),
	m_slider(0.f),
	m_function(function)
{
	m_range.sort();
	set_points();
	set_value(m_range.min);
}

void hgui::kernel::Slider::draw() const
{
	const auto activeBar = std::make_shared<shape::StraightLine>(std::get<1>(m_points), m_slider, m_activeBarColor, m_size.height / 4.f);
	const auto inactiveBar = std::make_shared<shape::StraightLine>(m_slider, std::get<2>(m_points), m_inactiveBarColor, m_size.height / 4.f);
	const auto slider = std::make_shared<shape::Circle>(m_slider, m_size.height / 2.f, m_color, true, 0.f);
	activeBar->draw(m_position, m_size, m_angularRotation);
	inactiveBar->draw(m_position, m_size, m_angularRotation);
	slider->draw(m_position, m_size, m_angularRotation);
}

bool hgui::kernel::Slider::is_inside(const point& point) const
{
	const hgui::point center(std::get<0>(m_points)),
		left(std::get<1>(m_points)),
		right(std::get<2>(m_points));
	const HGUI_PRECISION a = right.y - left.y;
	const HGUI_PRECISION b = left.x - right.x;
	const HGUI_PRECISION c = right.x * left.y - left.x * right.y;
	const bool nearPoint = hgui::kernel::distance(m_slider, point) <= m_size.height / 2.f || hgui::kernel::distance(right, point) <= m_size.height / 8.f ||
		hgui::kernel::distance(left, point) <= m_size.height / 8.f;
	if (std::abs(a) < 1e-6f)
	{
		return nearPoint || (point.x >= std::min(right.x, left.x) &&
			point.x <= std::max(right.x, left.x) &&
			std::abs(left.y - point.y) <= m_size.height / 8.f);
	}
	else if (std::abs(b) < 1e-6f)
	{
		return nearPoint || (point.y >= std::min(right.y, left.y) &&
			point.y <= std::max(right.y, left.y) &&
			std::abs(left.x - point.x) <= m_size.height / 8.f);
	}
	else
	{
		return nearPoint ||
			(std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b) <= m_size.height / 8.f &&
				point.x >= std::min(right.x, left.x) &&
				point.x <= std::max(right.x, left.x) &&
				point.y >= std::min(right.y, left.y) &&
				point.y <= std::max(right.y, left.y));
	}
}

HGUI_PRECISION hgui::kernel::Slider::get_value() const
{
	return m_range.round(m_range.min + distance(std::get<1>(m_points), m_slider) / distance(std::get<1>(m_points), std::get<2>(m_points)) * (m_range.max - m_range.min));
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

void hgui::kernel::Slider::set_position(const point& newPosition)
{
	const HGUI_PRECISION value = get_value();
	Widget::set_position(newPosition);
	set_points();
	set_value(value);
}

void hgui::kernel::Slider::set_rotation(const HGUI_PRECISION newAngularRotation)
{
	const HGUI_PRECISION old = m_angularRotation;
	Widget::set_rotation(newAngularRotation);
	set_points();
	m_slider = clamp(hgui::point::rotate(hgui::point::rotate(m_slider, std::get<0>(m_points), -old), std::get<0>(m_points), newAngularRotation));
}

void hgui::kernel::Slider::set_value(HGUI_PRECISION newValue)
{
	const hgui::point left(std::get<1>(m_points)),
		right(std::get<2>(m_points));
	newValue = m_range.round(std::clamp(newValue, m_range.min, m_range.max));
	const HGUI_PRECISION offset = (newValue - m_range.min) / (m_range.max - m_range.min) * hgui::kernel::distance(left, right);
	point direction = right - left; direction.normalize();
	m_slider = clamp(left + offset * direction);
}

void hgui::kernel::Slider::set_range(const Ranges& newRange)
{
	m_range = newRange;
	m_range.sort();
}

void hgui::kernel::Slider::set_slider_position(point newPosition)
{
	const hgui::point left(std::get<1>(m_points)),
		right(std::get<2>(m_points));
	point AB = right - left,
		AP = newPosition - left;
	HGUI_PRECISION projection = hgui::kernel::dot(AP, AB) / hgui::kernel::dot(AB, AB);
	if (projection < 0)
	{
		newPosition = left;
	}
	else if (projection > 1)
	{
		newPosition = right;
	}
	else
	{
		newPosition = left + projection * AB;
	}
	if (auto function = std::get_if<std::function<void()>>(&m_function))
	{
		m_slider = clamp(newPosition);
		if (*function)
		{
			(*function)();
		}
	}
	else if (auto function = std::get_if<std::function<void(HGUI_PRECISION, HGUI_PRECISION, std::shared_ptr<Slider>)>>(&m_function))
	{
		HGUI_PRECISION pastValue = get_value();
		m_slider = clamp(newPosition);
		if (*function)
		{
			(*function)(get_value(), pastValue, std::dynamic_pointer_cast<Slider>(shared_from_this()));
		}
	}
}

void hgui::kernel::Slider::set_function(const Function& newFunction)
{
	m_function = newFunction;
}

hgui::point hgui::kernel::Slider::clamp(const point& value) const
{
	if (m_range.step)
	{
		const point left(std::get<1>(m_points)),
			right(std::get<2>(m_points));
		point direction = right - left; direction.normalize();
		const HGUI_PRECISION size = hgui::kernel::distance(left, right),
			offset = size / m_range.step;
		point actualPoint = left,
			minPoint = actualPoint;
		HGUI_PRECISION minDistance = hgui::kernel::distance(value, actualPoint);
		while (hgui::kernel::distance(left, actualPoint) < size)
		{
			actualPoint += offset * direction;
			HGUI_PRECISION distance = hgui::kernel::distance(value, actualPoint);
			if (distance < minDistance)
			{
				minDistance = distance;
				minPoint = actualPoint;
			}
		}
		return minPoint;
	}
	else
	{
		return value;
	}
}

void hgui::kernel::Slider::set_points()
{
	auto center = m_position + m_size / 2.f;
	m_points = std::make_tuple(center,
		hgui::point::rotate(m_position + hgui::point(m_size.height / 8.f, m_size.height / 2.f), center, m_angularRotation),
		hgui::point::rotate(m_position + hgui::point(m_size.width - m_size.height / 8.f, m_size.height / 2.f), center, m_angularRotation));
}

HGUI_PRECISION hgui::kernel::Ranges::round(HGUI_PRECISION value) const
{
	HGUI_PRECISION factor = static_cast<HGUI_PRECISION>(std::pow(10, precision));
	return std::round(value * factor) / factor;
}

void hgui::kernel::Ranges::sort()
{
	min = std::min(min, max);
	max = std::max(min, max);
}
