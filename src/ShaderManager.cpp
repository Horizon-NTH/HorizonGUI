#include "../include/hgui/header/ShaderManager.h"
#include "../include/hgui/header/Shader.h"

#if defined(HGUI_DYNAMIC)
std::shared_ptr<hgui::kernel::Shader> hgui::ShaderManager::create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode)
{
	return std::make_shared<kernel::Shader>(vertexShaderCode, fragmentShaderCode, geometryShaderCode);
}
#elif defined(HGUI_STATIC)
std::map<std::string, std::shared_ptr<hgui::kernel::Shader>> hgui::ShaderManager::m_shaders;

std::shared_ptr<hgui::kernel::Shader>& hgui::ShaderManager::create(const std::string& shaderID, const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode)
{
	if (!m_shaders.contains(shaderID))
	{
		m_shaders[shaderID] = std::make_shared<kernel::Shader>(vertexShaderCode, fragmentShaderCode, geometryShaderCode);
		return m_shaders[shaderID];
	}
	throw std::runtime_error(("THERE IS ALREADY A SHADER WITH THE ID : " + shaderID).c_str());
}

std::shared_ptr<hgui::kernel::Shader>& hgui::ShaderManager::get(const std::string& shaderID)
{
	if (m_shaders.contains(shaderID))
	{
		return m_shaders[shaderID];
	}
	throw std::runtime_error(("THERE IS NO SHADER WITH THE ID : " + shaderID).c_str());
}

void hgui::ShaderManager::destroy(const std::initializer_list<std::string>& shadersID)
{
	if (shadersID.size())
	{
		for (const std::string& id : shadersID)
		{
			m_shaders.erase(id);
		}
	}
	else
	{
		m_shaders.clear();
	}
}
#endif
