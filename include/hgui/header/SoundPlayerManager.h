#pragma once

#include "Include.h"
#include "SoundPlayer.h"

namespace hgui
{
	void init();

	namespace kernel
	{
		void resources_cleaner();
	}

	class SoundPlayerManager
	{
	public:
		SoundPlayerManager() = delete;
		~SoundPlayerManager() = delete;
		SoundPlayerManager(const SoundPlayerManager& soundPlayerManager) = delete;
		SoundPlayerManager(SoundPlayerManager&& soundPlayerManager) = delete;

		SoundPlayerManager& operator=(const SoundPlayerManager& soundPlayerManager) = delete;
		SoundPlayerManager& operator=(SoundPlayerManager&& soundPlayerManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::SoundPlayer> create(const std::shared_ptr<kernel::Audio>& audio);

	private:
		static ALCdevice* m_device;
		static ALCcontext* m_context;
		static std::vector<std::weak_ptr<kernel::SoundPlayer>> m_players;

		static void init();
		static void clean();

		friend void kernel::resources_cleaner();
		friend void hgui::init();
	};
}
