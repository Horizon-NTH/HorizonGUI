#pragma once

#include "Coordinate.hpp"

namespace hgui::kernel
{
	class Monitor;
	class Image;

	class Window
	{
		using SizeCallback = std::function<void(GLFWwindow*, int, int)>;
		using PositionCallback = std::function<void(GLFWwindow*, int, int)>;

	public:
		Window(const std::string& name, const size& size, point position, const std::shared_ptr<Image>& icon, const std::shared_ptr<Monitor>& monitor, const std::map<options, bool>& options);
		Window(const Window& window) = delete;
		Window(Window&& window) = delete;

		~Window();

		Window& operator=(const Window& window) = delete;
		Window& operator=(Window&& window) = delete;

		[[nodiscard]] const size& get_size() const;
		void set_size(const size& newSize) const;

		[[nodiscard]] const point& get_position() const;
		void set_position(const point& newPosition);

		[[nodiscard]] GLFWwindow* get_window_ptr() const;

		void set_size_callback(const std::variant<std::function<void()>, SizeCallback>& function);
		void set_position_callback(const std::variant<std::function<void()>, PositionCallback>& function);

	private:
		std::string m_name;
		GLFWwindow* m_windowPTR;
		size m_size;
		point m_position;
		std::variant<std::function<void()>, SizeCallback> m_sizeCallback;
		std::variant<std::function<void()>, PositionCallback> m_positionCallback;

		static void size_callback(GLFWwindow* window, int width, int height);
		static void position_callback(GLFWwindow* window, int xPosition, int yPosition);
	};
}
