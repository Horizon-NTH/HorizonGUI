#pragma once

#include "Include.h"
#include "Define.h"
#include "Shader.h"

namespace hgui
{
#if defined(HGUI_DYNAMIC)
	class ShaderManager
	{
	public:
		static std::shared_ptr<kernel::Shader> create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode = "");
	
	private:
		ShaderManager() = delete;
	};
#elif defined(HGUI_STATIC)
	class ShaderManager
	{
	public:
		static std::shared_ptr<kernel::Shader>& create(const std::string& shaderID, const std::string& vertexShaderCode,
		                                               const std::string& fragmentShaderCode, const std::string& geometryShaderCode = "");
		static std::shared_ptr<kernel::Shader>& get(const std::string& shaderID);
		static void destroy(const std::initializer_list<std::string>& shadersID);

	private:
		ShaderManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Shader>> m_shaders;

		friend void kernel::resources_cleaner();
	};
#endif
}
