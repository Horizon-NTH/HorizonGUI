#pragma once

#include "Coordinate.hpp"
#include "Slider.h"

namespace hgui
{
	namespace kernel
	{
		class Cursor;
	}

	class SliderManager
	{
		using Function = std::variant<std::function<void()>, std::function<void(HGUI_PRECISION, HGUI_PRECISION, std::shared_ptr<kernel::Slider>)>>;

	public:
		SliderManager() = delete;
		~SliderManager() = delete;
		SliderManager(const SliderManager& sliderManager) = delete;
		SliderManager(SliderManager&& sliderManager) = delete;

		SliderManager& operator=(const SliderManager& sliderManager) = delete;
		SliderManager& operator=(SliderManager&& sliderManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Slider> create(const kernel::Ranges& range, const size& size, const point& position, const std::tuple<color, color, color>& colors = {HGUI_COLOR_WHITE, color("#424242"), color("#097fe0")}, const Function& function = {});
	};
}
