#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Shader;
		class Buffer;
		class Window;
	}

	class Timer;
	double get_delta_time();

#if defined(HGUI_DYNAMIC)
	class Renderer
	{
		friend class kernel::Window;

	public:
		Renderer() = delete;
		~Renderer() = delete;
		Renderer(const Renderer& bufferManager) = delete;
		Renderer(Renderer&& bufferManager) = delete;

		Renderer& operator=(const Renderer& bufferManager) = delete;
		Renderer& operator=(Renderer&& bufferManager) = delete;

		static void draw(const std::vector<std::string>& tags = {}, const effects& postProcessingOption = effects::CLASSIC);
		static void loop();
		static void set_background_color(const color& newColor);
		[[nodiscard]] static const color& get_background_color();
		static void set_draw_callback(const std::function<void()>& function);

	private:
		static void render();

		static std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, effects>> m_draws;
		static color m_backGroundColor;
		static std::shared_ptr<kernel::Buffer> m_frameBuffer;
		static std::shared_ptr<kernel::Shader> m_frameBufferShader;
		static std::function<void()> m_drawCallBack;
		static std::shared_ptr<Timer> m_timer;
		static double m_deltaTime;

		static
		void buffer_update();

		friend double get_delta_time();
	};
#elif defined(HGUI_STATIC)
	class Renderer
	{
	public:
		Renderer() = delete;
		~Renderer() = delete;
		Renderer(const Renderer& bufferManager) = delete;
		Renderer(Renderer&& bufferManager) = delete;

		Renderer& operator=(const Renderer& bufferManager) = delete;
		Renderer& operator=(Renderer&& bufferManager) = delete;

		static void draw(const std::vector<std::string>& tags = {}, const effects& postProcessingOption = effects::CLASSIC);
		static void loop();
		static void set_background_color(const color& newColor);
		[[nodiscard]] static const color& get_background_color();
		static void set_draw_callback(const std::function<void()>& function);

	private:
		static void render();

		static std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, effects>> m_draws;
		static color m_backGroundColor;
		static std::function<void()> m_drawCallBack;

		static void buffer_update();
	};
#endif
}
