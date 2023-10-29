#pragma once

#include "Include.h"
#include "TaskManager.h"
#include "Image.h"

namespace hgui
{
	void after(const std::chrono::milliseconds& delay, const std::function<void()>& function);
	[[nodiscard]] std::shared_ptr<kernel::Image> image_loader(const std::string& imagePath);
	[[nodiscard]] std::string file_reader(const std::string& filePath);
	[[nodiscard]] bool random(double chances);
	[[nodiscard]] std::string get_unique_id();
}
