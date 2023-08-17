#pragma once

#include "Include.h"
#include "Define.h"
#include "Widget.h"
#include "BufferManager.h"
#include "WindowManager.h"
#include "KeyBoardManager.h"
#include "TaskManager.h"
#include "TagManager.h"

namespace hgui
{
	typedef std::pair<std::string, effects> RenderOption;

	class RenderManager
	{
	public:
		static void draw(const std::vector<std::string>& tags = {}, const effects& postProcessingOption = effects::CLASSIC);
		static void loop();
		static void set_background_color(const color& newColor);
		static const color& get_background_color();

	private:
		RenderManager() = delete;

		static void render();

		static std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, effects>> m_draws;
		static color m_backGroundColor;
	};
}

