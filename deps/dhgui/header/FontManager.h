#pragma once

#include "Include.h"
#include "Define.h"
#include "Font.h"

namespace hgui
{
	class FontManager
	{
	public:
		static std::shared_ptr<kernel::Font> create(const std::string& fontPath);

	private:
		FontManager() = delete;
	};
}