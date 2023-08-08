#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Define.h"
#include "Image.h"
#include "Monitor.h"

namespace hgui
{
	namespace kernel
	{
		class Image;

		class Window
		{
		public:
			Window(const std::string& name, const size& size, const point& position, const std::shared_ptr<Image>& icon, const std::shared_ptr<Monitor>& monitor, const std::initializer_list<std::pair<options, bool>>& options);
			~Window();

			const size& get_size() const;
			void set_size(const size& newSize);

			const point& get_position();
			void set_position(const point& newPosition);

			GLFWwindow* get_windowPTR() const;

		private:
			std::string m_name;
			GLFWwindow* m_windowPTR;
			size m_size;
			point m_position;

			static void size_callback(GLFWwindow* window, int width, int height);
			static void position_callback(GLFWwindow* window, int xPostion, int yPosition);
		};
	}
}

