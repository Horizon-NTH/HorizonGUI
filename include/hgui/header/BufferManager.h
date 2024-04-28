#pragma once

#include "Coordinate.hpp"

namespace hgui
{
	namespace kernel
	{
		class Buffer;
		class Shader;
	}

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
}
