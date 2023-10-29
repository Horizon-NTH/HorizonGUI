#pragma once

#include "Include.h"
#include "ShaderManager.h"
#include "Widget.h"
#include "MouseManager.h"
#include "KeyBoardManager.h"
#include "LabelManager.h"
#include "SpriteManager.h"
#include "CanvasManager.h"
#include "CursorManager.h"
#include "ButtonManager.h"
#include "WindowManager.h"
#include "FontManager.h"
#include "BufferManager.h"
#include "MonitorManager.h"

namespace hgui
{
	void init();
	void end();

	namespace kernel
	{
		bool init_glfw();
		void init_glad();
#if defined(HGUI_STATIC)
		void init_resources();
#endif
		void resources_cleaner();
		void debug(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message,
		           const void* userParam);
	}
}
