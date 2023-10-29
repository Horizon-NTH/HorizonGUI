#pragma once

#include "Include.h"
#include "TaskManager.h"
#include "Image.h"

namespace hgui
{
	void after(const std::chrono::milliseconds& delay, const std::function<void()>& function);
	std::shared_ptr<kernel::Image> image_loader(const std::string& imagePath);
	std::string file_reader(const std::string& filePath);
	bool random(double chances);
	std::string get_unique_id();
}
