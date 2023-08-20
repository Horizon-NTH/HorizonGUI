#pragma once

#include "Include.h"
#include "Define.h"
#include "Maths.hpp"
#include "Buffer.h"
#include "Shader.h"
#include "Image.h"
#include "TextureManager.h"

namespace hgui
{
	class BufferManager
	{
	public:
		static std::shared_ptr<kernel::Buffer> create(const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize);

	private:
		BufferManager() = delete;
	};
}
