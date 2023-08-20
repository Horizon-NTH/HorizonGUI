#pragma once

#include "Include.h"
#include "Define.h"
#include "Texture.h"

namespace hgui
{
	class TextureManager
	{
	public:
		static std::shared_ptr<kernel::Texture> create(const std::shared_ptr<kernel::Image>& image);

	private:
		TextureManager() = delete;
	};
}