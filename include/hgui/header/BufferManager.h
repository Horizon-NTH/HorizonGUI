#pragma once

#include "Include.h"
#include "Maths.hpp"
#include "Buffer.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Image.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
	}

	class BufferManager
	{
	public:
		static const std::shared_ptr<kernel::Buffer>& create(const std::string& bufferID, const std::shared_ptr<kernel::Shader>& shader, const size& bufferSize);
		static const std::shared_ptr<kernel::Buffer>& get(const std::string& bufferID);
		static void delete_buffers(const std::initializer_list<std::string>& buffersID = {});

	private:
		BufferManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Buffer>> m_buffers;

		friend void kernel::resources_cleaner();
	};
}

