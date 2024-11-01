#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Font;
		class Shader;
		class Label;
	}

	class LabelManager
	{
	public:
		LabelManager() = delete;
		~LabelManager() = delete;
		LabelManager(const LabelManager& labelManager) = delete;
		LabelManager(LabelManager&& labelManager) = delete;

		LabelManager& operator=(const LabelManager& labelManager) = delete;
		LabelManager& operator=(LabelManager&& labelManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Label> create(const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, bool align = true, const std::tuple<unsigned int, color, HGUI_PRECISION>& textOptions = {12u, HGUI_COLOR_WHITE, 1.0f}, HGUI_PRECISION rotation = 0.0f);

	private:
		static inline std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
}
