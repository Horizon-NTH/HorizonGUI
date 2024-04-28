#pragma once

#include "Include.h"

namespace hgui
{
	namespace kernel
	{
		class Shader;
#if defined(HGUI_STATIC)
		void resources_cleaner();
#endif
	}

#if defined(HGUI_DYNAMIC)
	class ShaderManager
	{
	public:
		ShaderManager() = delete;
		~ShaderManager() = delete;
		ShaderManager(const ShaderManager& shaderManager) = delete;
		ShaderManager(ShaderManager&& shaderManager) = delete;

		ShaderManager& operator=(const ShaderManager& shaderManager) = delete;
		ShaderManager& operator=(ShaderManager&& shaderManager) = delete;

		[[nodiscard]] static std::shared_ptr<kernel::Shader> create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode = "");
	};
#elif defined(HGUI_STATIC)
	class ShaderManager
	{
	public:
		ShaderManager() = delete;
		~ShaderManager() = delete;
		ShaderManager(const ShaderManager& bufferManager) = delete;
		ShaderManager(ShaderManager&& bufferManager) = delete;

		ShaderManager& operator=(const ShaderManager& bufferManager) = delete;
		ShaderManager& operator=(ShaderManager&& bufferManager) = delete;

		static std::shared_ptr<kernel::Shader>& create(const std::string& shaderID, const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode = "");
		[[nodiscard]] static std::shared_ptr<kernel::Shader>& get(const std::string& shaderID);
		static void destroy(const std::initializer_list<std::string>& shadersID);

	private:
		static std::map<std::string, std::shared_ptr<kernel::Shader>> m_shaders;

		friend void kernel::resources_cleaner();
	};
#endif
}
