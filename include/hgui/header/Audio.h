#pragma once

#include "Include.h"

namespace hgui::kernel
{
	struct AudioData
	{
		sf_count_t frames;
		int samplerate;
		int channels;
		int format;
		int sections;
		int seekable;

		AudioData();
		explicit AudioData(const SF_INFO& info);
	};

	class Audio
	{
	public:
		explicit Audio(const std::string& filePath);

		[[nodiscard]] const float* data() const;
		[[nodiscard]] const AudioData& get_audio_data() const;

	private:
		AudioData m_audioData;
		std::vector<float> m_data;
	};
}
