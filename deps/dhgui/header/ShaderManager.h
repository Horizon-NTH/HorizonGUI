#pragma once

#include "Include.h"
#include "Define.h"
#include "Shader.h"

namespace hgui
{
	class ShaderManager
	{
	public:
		static std::shared_ptr<kernel::Shader> create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode = "");
	
	private:
		ShaderManager() = delete;
	};
}