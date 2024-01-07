#include "../include/hgui/header/SoundPlayerManager.h"

#if defined(HGUI_DYNAMIC)
ALCdevice* hgui::SoundPlayerManager::m_device(nullptr);
ALCcontext* hgui::SoundPlayerManager::m_context(nullptr);
std::vector<std::weak_ptr<hgui::kernel::SoundPlayer>> hgui::SoundPlayerManager::m_players;

std::shared_ptr<hgui::kernel::SoundPlayer> hgui::SoundPlayerManager::create(const std::shared_ptr<kernel::Audio>& audio)
{
	auto player = std::make_shared<kernel::SoundPlayer>(audio);
	m_players.push_back(player);
	return player;
}

void hgui::SoundPlayerManager::init()
{
	m_device = alcOpenDevice(nullptr);
	std::stringstream error;
	if (!m_device)
	{
		error << "ERROR " << alGetError() << " WHILE OPENING SOUND DEVICE";
		throw std::runtime_error(error.str());
	}
	m_context = alcCreateContext(m_device, nullptr);
	if (!m_context)
	{
		error << "ERROR " << alGetError() << " WHILE CREATING CONTEXT FOR DEVICE : " << m_device;
		alcCloseDevice(m_device);
		throw std::runtime_error(error.str());
	}
	if (!alcMakeContextCurrent(m_context))
	{
		error << "ERROR " << alGetError() << " WHILE SETTING CONTEXT (" << m_context << ") CURRENT FOR DEVICE : " << m_device;
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
		throw std::runtime_error(error.str());
	}
}

void hgui::SoundPlayerManager::clean()
{
	for (const auto& player : m_players)
	{
		if (const auto ptr = player.lock())
			ptr->clear();
	}
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}
#elif defined(HGUI_STATIC)

std::shared_ptr<hgui::kernel::SoundPlayer>& hgui::SoundPlayerManager::create(const std::string& soundPlayerID, const std::shared_ptr<kernel::Audio>& audio)
{
	if (!m_soundPlayers.contains(soundPlayerID))
	{
		m_soundPlayers[soundPlayerID] = std::make_shared<kernel::SoundPlayer>(audio);
		return m_soundPlayers[soundPlayerID];
	}
	throw std::runtime_error(("THERE IS ALREADY A SOUND PLAYER WITH THE ID : " + soundPlayerID).c_str());
}

std::shared_ptr<hgui::kernel::SoundPlayer>& hgui::SoundPlayerManager::get(const std::string& soundPlayerID)
{
	if (m_soundPlayers.contains(soundPlayerID))
	{
		return m_soundPlayers[soundPlayerID];
	}
	throw std::runtime_error(("THERE IS NO SOUND PLAYER WITH THE ID : " + soundPlayerID).c_str());
}

void hgui::SoundPlayerManager::destroy(const std::initializer_list<std::string>& soundPlayerID)
{
	if (soundPlayerID.size())
	{
		for (const std::string& id : soundPlayerID)
		{
			m_soundPlayers.erase(id);
		}
	}
	else
	{
		m_soundPlayers.clear();
	}
}

void hgui::SoundPlayerManager::init()
{
	m_device = alcOpenDevice(nullptr);
	std::stringstream error;
	if (!m_device)
	{
		error << "ERROR " << alGetError() << " WHILE OPENING SOUND DEVICE";
		throw std::runtime_error(error.str());
	}
	m_context = alcCreateContext(m_device, nullptr);
	if (!m_context)
	{
		error << "ERROR " << alGetError() << " WHILE CREATING CONTEXT FOR DEVICE : " << m_device;
		alcCloseDevice(m_device);
		throw std::runtime_error(error.str());
	}
	if (!alcMakeContextCurrent(m_context))
	{
		error << "ERROR " << alGetError() << " WHILE SETTING CONTEXT (" << m_context << ") CURRENT FOR DEVICE : " << m_device;
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
		throw std::runtime_error(error.str());
	}
}

void hgui::SoundPlayerManager::clean()
{
	for (const auto& player : m_soundPlayers | std::views::values)
	{
		player->clear();
	}
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}
#endif
