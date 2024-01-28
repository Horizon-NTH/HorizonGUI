#pragma once

#include "Include.h"

namespace hgui
{
	class SoundPlayerManager;
}

namespace hgui::kernel
{
	class Audio;

	class SoundPlayer
	{
		friend class hgui::SoundPlayerManager;

	public:
		explicit SoundPlayer(const std::shared_ptr<Audio>& audio);
		~SoundPlayer();

		void play() const;
		void pause() const;
		void stop() const;

		void loop() const;
		void stop_loop() const;

		[[nodiscard]] bool is_playing() const;
		[[nodiscard]] bool is_looping() const;

		void set_volume(float volume) const;
		[[nodiscard]] float get_volume() const;

	private:
		ALuint m_buffer;
		ALuint m_source;
		bool m_cleared;

		static void check_error(const std::string& message);
		void clear();
	};
}
