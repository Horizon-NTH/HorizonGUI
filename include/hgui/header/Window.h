#pragma once

#include "Include.h"
#include "Image.h"
#include "Monitor.h"

namespace hgui
{
	namespace kernel
	{
		class Image;

		enum WindowOptions
		{
			RESIZABLE = 0x00020003,
			VISIBLE = 0x00020004,
			DECORATED = 0x00020005,
			FOCUSED = 0x00020001,
			AUTO_ICONIFY = 0x00020006,
			FLOATING = 0x00020007,
			MAXIMAIZED = 0x00020008,
			CENTER_CURSOR = 0x00020009,
			FOCUS_ON_SHOW = 0x0002000C,
			SCALE_TO_MONITOR = 0x0002200C
		};

		class Window
		{
		public:
			Window(const std::string& name, glm::vec2 size, glm::vec2 position, const std::shared_ptr<Image>& icon = nullptr, std::initializer_list<std::pair<WindowOptions, bool>> options = {});
			~Window();

			glm::vec2 get_size() const;
			void set_size(glm::vec2 newSize);
			void set_fullscreen(const std::shared_ptr<Monitor>& monitor);

			glm::vec2 get_position();
			void set_position(glm::vec2 newPosition);

			GLFWwindow* get_windowPTR() const;

		private:
			std::string m_name;
			GLFWwindow* m_windowPTR;
			glm::vec2 m_size;
			glm::vec2 m_position;

			static void size_callback(GLFWwindow* window, int width, int height);
			static void position_callback(GLFWwindow* window, int xPostion, int yPosition);
		};
	}
}

