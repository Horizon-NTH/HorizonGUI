#pragma once

#include "Include.h"
#include "Buffer.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Tools.h"
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
		static const std::shared_ptr<kernel::Buffer>& create(const std::string& bufferName, const std::shared_ptr<kernel::Shader>& shader);
		static const std::shared_ptr<kernel::Buffer>& get(const std::string& bufferName);
		static void delete_buffers(std::initializer_list<std::string> buffersNames = {});

	private:
		BufferManager();

		static std::map<std::string, std::shared_ptr<kernel::Buffer>> m_buffers;

		friend void kernel::resources_cleaner();
	};
}

