#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Shader;
		class Buffer;
		class Window;
		void resources_cleaner();
	}

	class Timer;
	double get_delta_time();

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

		static inline std::pair<std::vector<std::string>, std::pair<std::vector<std::string>, effects>> m_draws;
		static inline color m_backGroundColor;
		static inline std::shared_ptr<kernel::Buffer> m_frameBuffer;
		static inline std::shared_ptr<kernel::Shader> m_frameBufferShader;
		static inline std::function<void()> m_drawCallBack;
		static inline std::shared_ptr<Timer> m_timer;
		static inline double m_deltaTime = 0.;

		static void buffer_update();

		friend double get_delta_time();
		friend void kernel::resources_cleaner();
	};
}
