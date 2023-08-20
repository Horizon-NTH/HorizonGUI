#pragma once

#include "Include.h"
#include "ShaderManager.h"
#include "Widget.h"
#include "MouseManager.h"
#include "KeyBoardManager.h"
#include "LabelManager.h"
#include "SpriteManager.h"
#include "CanvaManager.h"
#include "CursorManager.h"
#include "ButtonManager.h"
#include "WindowManager.h"
#include "FontManager.h"
#include "MonitorManager.h"

namespace hgui
{
	/*Founction that initialize the HorizonGUI library.*/
	void init();
	void end();

	namespace kernel
	{
		bool init_glfw();
		void init_glad();

		void resources_cleaner();
		void debug(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	}
}

