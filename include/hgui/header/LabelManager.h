#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "TagManager.h"
#include "ShaderManager.h"
#include "Font.h"
#include "Label.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class LabelManager
	{
	public:
		LabelManager() = delete;
		~LabelManager() = delete;
		LabelManager(const LabelManager& bufferManager) = delete;
		LabelManager(LabelManager&& bufferManager) = delete;

		LabelManager& operator=(const LabelManager& bufferManager) = delete;
		LabelManager& operator=(LabelManager&& bufferManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Label> create(const std::string& text, const point& position, const std::shared_ptr<kernel::Font>& font, const std::tuple<unsigned int, color, float>& textOptions = { 12u, HGUI_COLOR_WHITE, 1.0f });

	private:
		static std::shared_ptr<kernel::Shader> m_shader;

		friend void kernel::resources_cleaner();
	};
#elif defined(HGUI_STATIC)
	class LabelManager
	{
	public:
		LabelManager() = delete;
		~LabelManager() = delete;
		LabelManager(const LabelManager& bufferManager) = delete;
		LabelManager(LabelManager&& bufferManager) = delete;

		LabelManager& operator=(const LabelManager& bufferManager) = delete;
		LabelManager& operator=(LabelManager&& bufferManager) = delete;

		static const std::shared_ptr<kernel::Label>& create(const std::string& labelID, const std::string& text, const point& position,
		                                                    const std::shared_ptr<kernel::Font>& font,
		                                                    const std::tuple<unsigned int, color, float>& textOptions = {
					                                                    12u, HGUI_COLOR_WHITE, 1.0f
				                                                    });
		[[nodiscard]] static const std::shared_ptr<kernel::Label>& get(const std::string& labelID);
		static void destroy(const std::initializer_list<std::string>& labelsID = {});

	private:
		static std::map<std::string, std::shared_ptr<kernel::Label>> m_labels;

		friend void kernel::resources_cleaner();
	};
#endif
}
