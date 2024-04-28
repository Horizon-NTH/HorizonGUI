#pragma once

#include "Widget.h"

namespace hgui::kernel
{
	struct Ranges
	{
		HGUI_PRECISION min;
		HGUI_PRECISION max;
		unsigned int step = 0u;
		unsigned int precision = 2u;

		[[nodiscard]] HGUI_PRECISION round(HGUI_PRECISION value) const;
		void sort();
	};

	class Slider final : public Widget
	{
		using Function = std::variant<std::function<void()>, std::function<void(HGUI_PRECISION, HGUI_PRECISION, std::shared_ptr<Slider>)>>;

	public:
		Slider(const Ranges& range, const color& inactiveBarColor, const color& activeBarColor, const size& size, const point& position, const color& color, Function function);
		Slider(const Slider& slider) = default;
		Slider(Slider&& slider) = default;

		~Slider() override = default;

		Slider& operator=(const Slider& slider) = default;
		Slider& operator=(Slider&& slider) = default;

		void draw() const override;
		[[nodiscard]] bool is_inside(const point& point) const override;

		[[nodiscard]] HGUI_PRECISION get_value() const;
		[[nodiscard]] const Ranges& get_range() const;
		[[nodiscard]] const point& get_slider_position() const;
		[[nodiscard]] const Function& get_function() const;

		void set_position(const point& newPosition) override;
		void set_size(const size& newSize) override;
		void set_value(HGUI_PRECISION newValue);
		void set_range(const Ranges& newRange);
		void set_slider_position(point newPosition);
		void set_function(const Function& newFunction);

	private:
		Ranges m_range;
		color m_inactiveBarColor;
		color m_activeBarColor;
		point m_slider;
		std::pair<point, point> m_points;
		Function m_function;
		color m_color;

		point clamp(const point& value) const;
		void set_points();
	};
}
