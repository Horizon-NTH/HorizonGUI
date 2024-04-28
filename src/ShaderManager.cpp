#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/Shader.h"

std::shared_ptr<hgui::kernel::Shader> hgui::ShaderManager::create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode)
{
	return std::make_shared<kernel::Shader>(vertexShaderCode, fragmentShaderCode, geometryShaderCode);
}
