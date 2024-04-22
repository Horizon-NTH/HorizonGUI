#pragma once

#include "Coordinate.hpp"
#include "Slider.h"

namespace hgui
{
	namespace kernel
	{
		class Cursor;
	}

#if defined(HGUI_DYNAMIC)
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

		[[nodiscard]] static std::shared_ptr<kernel::Slider> create(const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor = color("#424242"), const color& activeBarColor = color("#097fe0"), const color& sliderColor = HGUI_COLOR_WHITE, const Function& function = {}, HGUI_PRECISION rotation = 0.f);

	private:
		friend void kernel::resources_cleaner();
	};
#elif defined(HGUI_STATIC)
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

		static const std::shared_ptr<kernel::Slider>& create(const std::string& sliderID, const kernel::Ranges& range, const size& size, const point& position, const color& inactiveBarColor = color(66), const color& activeBarColor = color(9, 127, 224), const color& sliderColor = HGUI_COLOR_WHITE, const Function& function = []
			{
			}, HGUI_PRECISION angularRotation = 0.f);
		[[nodiscard]] static const std::shared_ptr<kernel::Slider>& get(const std::string& sliderID);
		static void destroy(const std::initializer_list<std::string>& slidersID);

	private:
		static std::map<std::string, std::shared_ptr<kernel::Slider>> m_sliders;
		static std::shared_ptr<kernel::Cursor> m_cursor;

		friend void kernel::resources_cleaner();
	};
#endif
}
