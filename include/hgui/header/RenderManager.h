#pragma once

#include "Include.h"
#include "BufferManager.h"
#include "WidgetManager.h"
#include "Widget.h"
#include "WindowManager.h"
#include "KeyBoardManager.h"
#include "Tools.h"

namespace hgui
{
	namespace render
	{
		enum RenderOptions
		{
			CLASSIC,
			BLURRED,
			NEGATIVE
		};
	}
	typedef std::pair<std::string, render::RenderOptions> RenderOption;

	class RenderManager
	{
	public:
		static void draw(std::vector<std::string> tags = {}, render::RenderOptions postProcessingOption = render::CLASSIC);
		static void loop();
		static void set_background_color(glm::vec3 newColor);
		static glm::vec3 get_background_color();

	private:
		RenderManager();

		static void render();

		static std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, render::RenderOptions>> m_draws;
		static glm::vec3 m_backGroundColor;
	};
}

