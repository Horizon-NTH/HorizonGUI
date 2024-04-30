#pragma once

#include "Sprite.h"

namespace hgui::kernel
{
	class GIF;

	class AnimatedSprite final : public Sprite
	{
	public:
		AnimatedSprite(const std::shared_ptr<Shader>& shader, const std::shared_ptr<GIF>& gif, const size& size, const point& position, const color& color, float rotation);
		explicit AnimatedSprite(const Sprite& animatedSprite) = delete;
		AnimatedSprite(AnimatedSprite&& animatedSprite) = delete;

		~AnimatedSprite() override = default;

		AnimatedSprite& operator=(const AnimatedSprite& animatedSprite) = delete;
		AnimatedSprite& operator=(AnimatedSprite&& animatedSprite) = delete;

		[[nodiscard]] const std::shared_ptr<GIF>& get_gif() const;

		void set_gif(const std::shared_ptr<GIF>& gif);

		void play();
		void pause();
		void stop();
		void loop();
		void stop_loop();

		[[nodiscard]] bool is_playing() const;
		[[nodiscard]] bool is_looping() const;

	private:
		std::shared_ptr<GIF> m_gif;
		unsigned m_frameRendered;
		bool m_loop;
		std::string m_taskID;

		using Sprite::set_texture;
		void display();
	};
}
