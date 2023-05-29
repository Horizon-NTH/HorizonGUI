#pragma once

#include "Include.h"
#include "../HorizonGUI.h"

namespace hgui
{
	/*Founction that initialize the HorizonGUI library.*/
	void init();
	void end();

	namespace kernel
	{
		bool init_glfw();
		void init_glad();
		void init_resources();
		void resources_cleaner();
		void debug(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	}
}

