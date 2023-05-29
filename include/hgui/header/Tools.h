#pragma once

#include "Include.h"

namespace hgui
{
	void after(std::chrono::milliseconds delay, std::function<void()> function);
	std::string file_reader(const std::string& filePath);
}
