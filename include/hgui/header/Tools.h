#pragma once

#include "Include.h"
#include "TaskManager.h"

namespace hgui
{
	void after(const std::chrono::milliseconds& delay, const std::function<void()>& function);
	std::string file_reader(const std::string& filePath);
}
