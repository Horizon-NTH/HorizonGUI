#pragma once

#include "Include.h"
#include "Maths.hpp"

namespace hgui
{
	namespace kernel
	{
		class Shader
		{
		public:
			Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
			~Shader();

			const Shader& use() const;
			const GLuint get_id() const;

			const Shader& set_int(const std::string& uniformName, int i) const;
			const Shader& set_float(const std::string& uniformName, float f) const;
			const Shader& set_vec2(const std::string& uniformName, const vec2& vec2) const;
			const Shader& set_vec3(const std::string& uniformName, const vec3& vec3) const;
			const Shader& set_vec4(const std::string& uniformName, const vec4& vec4) const;
			const Shader& set_double(const std::string& uniformName, double d) const;
			const Shader& set_dvec2(const std::string& uniformName, const dvec2& vec2) const;
			const Shader& set_dvec3(const std::string& uniformName, const dvec3& vec3) const;
			const Shader& set_dvec4(const std::string& uniformName, const dvec4& vec4) const;
			const Shader& set_mat4(const std::string& uniformName, const glm::mat4& mat4) const;

		private:
			GLuint m_id;

			const GLuint load_shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode);
			void check_compile_error(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) const;
			void check_linking_error(GLuint shaderProgram) const;
		};
	}
}

