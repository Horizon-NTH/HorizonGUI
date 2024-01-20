#include "../include/hgui/header/SoundPlayer.h"
#include "../include/hgui/header/Audio.h"

hgui::kernel::SoundPlayer::SoundPlayer(const std::shared_ptr<Audio>& audio) :
	m_buffer(),
	m_source(),
	m_cleared(false)
{
	alGenBuffers(1, &m_buffer);
	check_error("BUFFER CREATION");

	alGenSources(1, &m_source);
	check_error("SOURCE CREATION");

	const auto data = audio->get_audio_data();
	const ALenum format = (data.channels == 1) ? AL_FORMAT_MONO_FLOAT32 : AL_FORMAT_STEREO_FLOAT32;
	alBufferData(m_buffer, format, audio->data(), static_cast<ALsizei>(data.frames * data.channels * sizeof(float)), data.samplerate);
	check_error("SETTING AUDIO DATA IN THE BUFFER");

	alSourcei(m_source, AL_BUFFER, static_cast<ALint>(m_buffer));
	check_error("ASSIGNING BUFFER TO SOURCE");
}

hgui::kernel::SoundPlayer::~SoundPlayer()
{
	clear();
}

void hgui::kernel::SoundPlayer::play() const
{
	alSourcePlay(m_source);
	check_error("AUDIO PLAYBACK");
}

void hgui::kernel::SoundPlayer::pause() const
{
	alSourcePause(m_source);
	check_error("PAUSING AUDIO");
}

void hgui::kernel::SoundPlayer::stop() const
{
	alSourceStop(m_source);
	check_error("STOPPING AUDIO");
}

void hgui::kernel::SoundPlayer::loop() const
{
	alSourcei(m_source, AL_LOOPING, AL_TRUE);
	check_error("SETTING THE AUDIO LOOP");
	play();
}

void hgui::kernel::SoundPlayer::stop_loop() const
{
	alSourcei(m_source, AL_LOOPING, AL_FALSE);
	check_error("UNSETTING THE AUDIO LOOP");
}

bool hgui::kernel::SoundPlayer::is_playing() const
{
	ALint state;
	alGetSourcei(m_source, AL_SOURCE_STATE, &state);
	check_error("CHECKING AUDIO STATE");
	return state == AL_PLAYING;
}

bool hgui::kernel::SoundPlayer::is_looping() const
{
	ALint loop;
	alGetSourcei(m_source, AL_LOOPING, &loop);
	check_error("CHECKNIG LOOPING STATE");
	return loop == AL_TRUE;
}

void hgui::kernel::SoundPlayer::set_volume(const float volume) const
{
	alSourcef(m_source, AL_GAIN, volume);
	check_error("SETTING VOLUME");
}

float hgui::kernel::SoundPlayer::get_volume() const
{
	ALfloat volume;
	alGetSourcef(m_source, AL_GAIN, &volume);
	check_error("GETTING VOLUME");
	return volume;
}

void hgui::kernel::SoundPlayer::check_error(const std::string& message)
{
	if (const ALenum error = alGetError(); error != AL_NO_ERROR)
	{
		std::stringstream errorMessage;
		errorMessage << "OPENAL ERROR (" << error << "): " << std::endl
				<< "ERROR OCCURED WHILE " << message;
		throw std::runtime_error(errorMessage.str());
	}
}

void hgui::kernel::SoundPlayer::clear()
{
	if (!m_cleared)
	{
		stop();
		alSourcei(m_source, AL_BUFFER, 0);
		alDeleteBuffers(1, &m_buffer);
		check_error("DELETING BUFFER");
		alDeleteSources(1, &m_source);
		check_error("DELETING SOURCE");
		m_cleared = true;
	}
}
