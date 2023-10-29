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
#if defined(HGUI_DYNAMIC)
	class BufferManager
	{
	public:
		[[nodiscard]] static std::shared_ptr<kernel::Buffer> create(const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize);

	private:
		BufferManager() = delete;
	};
#elif defined(HGUI_STATIC)
	class BufferManager
	{
	public:
		static const std::shared_ptr<kernel::Buffer>& create(const std::string& bufferID, const std::shared_ptr<kernel::Shader>& shader,
		                                                     const size& bufferSize);
		[[nodiscard]] static const std::shared_ptr<kernel::Buffer>& get(const std::string& bufferID);
		static void destroy(const std::initializer_list<std::string>& buffersID = {});

	private:
		BufferManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Buffer>> m_buffers;

		friend void kernel::resources_cleaner();
	};
#endif
}
