#include "../include/hgui/header/Audio.h"

hgui::kernel::AudioData::AudioData() :
	frames(),
	samplerate(),
	channels(),
	format(),
	sections(),
	seekable()
{
}

hgui::kernel::AudioData::AudioData(const SF_INFO& info) :
	frames(info.frames),
	samplerate(info.samplerate),
	channels(info.channels),
	format(info.format),
	sections(info.sections),
	seekable(info.seekable)
{
}

hgui::kernel::Audio::Audio(const std::string& filePath)
{
	SF_INFO info;
	SNDFILE* file = sf_open(filePath.c_str(), SFM_READ, &info);
	if (!file)
	{
		throw std::runtime_error("ERROR WHILE LOADING FILE : " + filePath);
	}
	m_data.resize(info.frames * info.channels);
	sf_read_float(file, m_data.data(), info.frames * info.channels);
	sf_close(file);
	m_audioData = AudioData(info);
}

const float* hgui::kernel::Audio::data() const
{
	return m_data.data();
}

const hgui::kernel::AudioData& hgui::kernel::Audio::get_audio_data() const
{
	return m_audioData;
}
