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
#if defined(HGUI_DYNAMIC)
	class Renderer
	{
	public:
		static void draw(const std::vector<std::string>& tags = {}, const effects& postProcessingOption = effects::CLASSIC);
		static void loop();
		static void set_background_color(const color& newColor);
		static const color& get_background_color();

	private:
		Renderer() = delete;

		static void render();

		static std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, effects>> m_draws;
		static color m_backGroundColor;
		static std::shared_ptr<kernel::Buffer> m_frameBuffer;
		static std::shared_ptr<kernel::Shader> m_frameBufferShader;
	};
#elif defined(HGUI_STATIC)
	class Renderer
	{
	public:
		static void draw(const std::vector<std::string>& tags = {}, const effects& postProcessingOption = effects::CLASSIC);
		static void loop();
		static void set_background_color(const color& newColor);
		static const color& get_background_color();

	private:
		Renderer() = delete;

		static void render();

		static std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, effects>> m_draws;
		static color m_backGroundColor;
	};
#endif
}

