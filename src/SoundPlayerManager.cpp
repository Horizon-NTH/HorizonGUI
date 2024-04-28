#include "../include/hgui/header/SoundPlayerManager.h"
#include "../include/hgui/header/SoundPlayer.h"

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
