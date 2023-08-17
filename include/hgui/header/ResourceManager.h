#pragma once

#include "Include.h"
#include "Shader.h"
#include "Texture.h"

namespace hgui
{
	namespace kernel
	{
		void resources_cleaner();
		void init_resources();
	}

	class ResourceManager
	{
	public:
		static std::shared_ptr<kernel::Shader>& load_shader(const std::string& shaderName, const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode = "");
		static std::shared_ptr<kernel::Shader>& get_shader(const std::string& shaderName);
		static void delete_shaders(const std::initializer_list<std::string>& shadersNames);

		static std::shared_ptr<kernel::Texture>& load_texture(const std::string& textureName, const std::shared_ptr<kernel::Image>& image);
		static std::shared_ptr<kernel::Texture>& get_texture(const std::string& textureName);
		static void delete_textures(const std::initializer_list<std::string>& texturesnames);

	private:
		ResourceManager() = delete;

		static std::map<std::string, std::shared_ptr<kernel::Shader>> m_shaders;
		static std::map<std::string, std::shared_ptr<kernel::Texture>> m_textures;
		static std::map<std::string, std::string> m_glsl;

		friend void kernel::resources_cleaner();
		friend void kernel::init_resources();
	};
}

