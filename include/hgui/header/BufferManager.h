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
		BufferManager() = delete;
		~BufferManager() = delete;
		BufferManager(const BufferManager& bufferManager) = delete;
		BufferManager(BufferManager&& bufferManager) = delete;

		BufferManager& operator=(const BufferManager& bufferManager) = delete;
		BufferManager& operator=(BufferManager&& bufferManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Buffer> create(const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize);
	};
#elif defined(HGUI_STATIC)
	class BufferManager
	{
	public:
		BufferManager() = delete;
		~BufferManager() = delete;
		BufferManager(const BufferManager& bufferManager) = delete;
		BufferManager(BufferManager&& bufferManager) = delete;

		BufferManager& operator=(const BufferManager& bufferManager) = delete;
		BufferManager& operator=(BufferManager&& bufferManager) = delete;

		static const std::shared_ptr<kernel::Buffer>& create(const std::string& bufferID, const std::shared_ptr<kernel::Shader>& shader,
		                                                     const size& bufferSize);
		[[nodiscard]] static const std::shared_ptr<kernel::Buffer>& get(const std::string& bufferID);
		static void destroy(const std::initializer_list<std::string>& buffersID = {});

	private:
		static std::map<std::string, std::shared_ptr<kernel::Buffer>> m_buffers;

		friend void kernel::resources_cleaner();
	};
#endif
}
