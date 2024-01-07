#pragma once

#include "Include.h"
#include "Image.h"
#include "Audio.h"
#include "GIF.h"

namespace hgui
{
	void after(const std::chrono::milliseconds& delay, const std::function<void()>& function);
	[[nodiscard]] std::shared_ptr<kernel::Image> image_loader(const std::string& imagePath);
	[[nodiscard]] std::shared_ptr<kernel::GIF> gif_loader(const std::string& gifPath);
	[[nodiscard]] std::shared_ptr<kernel::Audio> audio_loader(const std::string& audioPath);
	[[nodiscard]] std::string file_reader(const std::string& filePath);
	[[nodiscard]] bool random(double chances);
	[[nodiscard]] std::string get_unique_id();
}
