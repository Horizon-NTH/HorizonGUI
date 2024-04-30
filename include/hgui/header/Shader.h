#pragma once

#include "Coordinate.hpp"

namespace hgui::kernel
{
	class Shader
	{
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
		Shader(const Shader& shader) noexcept = delete;
		Shader(Shader&& shader) noexcept = delete;

		~Shader() noexcept;

		Shader& operator=(const Shader& shader) noexcept = delete;
		Shader& operator=(Shader&& shader) noexcept = delete;

		Shader& use() noexcept;
		[[nodiscard]] GLuint get_id() const noexcept;

		Shader& set_int(const std::string& uniformName, int i) noexcept;

		Shader& set_float(const std::string& uniformName, float f) noexcept;
		Shader& set_vec2(const std::string& uniformName, const vec2& vec2) noexcept;
		Shader& set_vec2(const std::string& uniformName, const point& vec2) noexcept;
		Shader& set_vec2(const std::string& uniformName, const size& vec2) noexcept;
		Shader& set_vec3(const std::string& uniformName, const vec3& vec3) noexcept;
		Shader& set_vec3(const std::string& uniformName, const color& vec3) noexcept;
		Shader& set_vec4(const std::string& uniformName, const vec4& vec4) noexcept;
		Shader& set_vec4(const std::string& uniformName, const color& vec4) noexcept;

		Shader& set_double(const std::string& uniformName, double d) noexcept;
		Shader& set_dvec2(const std::string& uniformName, const dvec2& dvec2) noexcept;
		Shader& set_dvec2(const std::string& uniformName, const Point<double>& dvec2) noexcept;
		Shader& set_dvec2(const std::string& uniformName, const Size<double>& dvec2) noexcept;
		Shader& set_dvec3(const std::string& uniformName, const dvec3& dvec3) noexcept;
		Shader& set_dvec3(const std::string& uniformName, const Color<double>& dvec3) noexcept;
		Shader& set_dvec4(const std::string& uniformName, const dvec4& dvec4) noexcept;
		Shader& set_dvec4(const std::string& uniformName, const Color<double>& dvec4) noexcept;

		Shader& set_mat4(const std::string& uniformName, const glm::mat4& mat4) noexcept;

	private:
		GLuint m_id;

		static GLuint load_shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode);

		static void check_compile_error(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader);
		static void check_linking_error(GLuint shaderProgram);
	};
}
