#pragma once

#include "Include.h"
#include "Tools.h"

namespace hgui
{
	namespace kernel
	{
		class Shader
		{
		public:
			Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			~Shader();

			const Shader& use() const;
			const GLuint get_id() const;

			const Shader& set_1f(const char* uniformName, float f) const;
			const Shader& set_1i(const char* uniformName, int i) const;
			const Shader& set_vec2f(const char* uniformName, glm::vec2 vec2) const;
			const Shader& set_vec3f(const char* uniformName, glm::vec3 vec3) const;
			const Shader& set_vec4f(const char* uniformName, glm::vec4 vec4) const;
			const Shader& set_mat4(const char* uniformName, glm::mat4 mat4) const;

		private:
			GLuint m_id;

			const GLuint load_shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			void check_compile_error(GLuint vertexShader, GLuint fragmentShader) const;
			void check_linking_error(GLuint shaderProgram) const;
		};
	}
}

