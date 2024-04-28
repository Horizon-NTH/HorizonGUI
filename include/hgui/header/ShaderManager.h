#pragma once

#include "Include.h"

namespace hgui
{
	namespace kernel
	{
		class Shader;
	}

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
}
