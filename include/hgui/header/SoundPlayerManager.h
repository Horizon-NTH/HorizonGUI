#pragma once

#include "Include.h"

namespace hgui
{
	void init();

	namespace kernel
	{
		class Audio;
		class SoundPlayer;
		void resources_cleaner();
	}

#if defined(HGUI_DYNAMIC)

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
		static inline ALCdevice* m_device = nullptr;
		static inline ALCcontext* m_context = nullptr;
		static inline std::vector<std::weak_ptr<kernel::SoundPlayer>> m_players = {};

		static void init();
		static void clean();

		friend void kernel::resources_cleaner();
		friend void hgui::init();
	};
#elif defined(HGUI_STATIC)
	class SoundPlayerManager
	{
	public:
		SoundPlayerManager() = delete;
		~SoundPlayerManager() = delete;
		SoundPlayerManager(const SoundPlayerManager& soundPlayerManager) = delete;
		SoundPlayerManager(SoundPlayerManager&& soundPlayerManager) = delete;

		SoundPlayerManager& operator=(const SoundPlayerManager& soundPlayerManager) = delete;
		SoundPlayerManager& operator=(SoundPlayerManager&& soundPlayerManager) = delete;

		static std::shared_ptr<kernel::SoundPlayer>& create(const std::string& soundPlayerID, const std::shared_ptr<kernel::Audio>& audio);
		[[nodiscard]] static std::shared_ptr<kernel::SoundPlayer>& get(const std::string& soundPlayerID);
		static void destroy(const std::initializer_list<std::string>& soundPlayerID);

	private:
		inline static ALCdevice* m_device{};
		inline static ALCcontext* m_context{};
		inline static std::map<std::string, std::shared_ptr<kernel::SoundPlayer>> m_soundPlayers{};

		static void init();
		static void clean();

		friend void kernel::resources_cleaner();
		friend void hgui::init();
	};
#endif
}
