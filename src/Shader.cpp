#include "../include/hgui/header/Shader.h"

hgui::kernel::Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader) :
	m_id(load_shader(vertexShader, fragmentShader, geometryShader))
{
}

hgui::kernel::Shader::~Shader() noexcept
{
	glDeleteProgram(m_id);
}

hgui::kernel::Shader& hgui::kernel::Shader::use() noexcept
{
	glUseProgram(m_id);
	return *this;
}

GLuint hgui::kernel::Shader::get_id() const noexcept
{
	return m_id;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_float(const std::string& uniformName, const float f) noexcept
{
	glUniform1f(glGetUniformLocation(m_id, uniformName.c_str()), f);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_int(const std::string& uniformName, const int i) noexcept
{
	glUniform1i(glGetUniformLocation(m_id, uniformName.c_str()), i);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_vec2(const std::string& uniformName, const vec2& vec2) noexcept
{
	glUniform2f(glGetUniformLocation(m_id, uniformName.c_str()), vec2.x, vec2.y);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_vec2(const std::string& uniformName, const point& vec2) noexcept
{
	glUniform2f(glGetUniformLocation(m_id, uniformName.c_str()), vec2.x, vec2.y);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_vec2(const std::string& uniformName, const size& vec2) noexcept
{
	glUniform2f(glGetUniformLocation(m_id, uniformName.c_str()), vec2.width, vec2.height);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_vec3(const std::string& uniformName, const vec3& vec3) noexcept
{
	glUniform3f(glGetUniformLocation(m_id, uniformName.c_str()), vec3.x, vec3.y, vec3.z);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_vec3(const std::string& uniformName, const color& vec3) noexcept
{
	glUniform3f(glGetUniformLocation(m_id, uniformName.c_str()), vec3.r, vec3.g, vec3.b);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_vec4(const std::string& uniformName, const vec4& vec4) noexcept
{
	glUniform4f(glGetUniformLocation(m_id, uniformName.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_vec4(const std::string& uniformName, const color& vec4) noexcept
{
	glUniform4f(glGetUniformLocation(m_id, uniformName.c_str()), vec4.r, vec4.g, vec4.b, vec4.a);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_double(const std::string& uniformName, const double d) noexcept
{
	glUniform1d(glGetUniformLocation(m_id, uniformName.c_str()), d);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_dvec2(const std::string& uniformName, const dvec2& dvec2) noexcept
{
	glUniform2d(glGetUniformLocation(m_id, uniformName.c_str()), dvec2.x, dvec2.y);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_dvec2(const std::string& uniformName, const Point<double>& dvec2) noexcept
{
	glUniform2d(glGetUniformLocation(m_id, uniformName.c_str()), dvec2.x, dvec2.y);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_dvec2(const std::string& uniformName, const Size<double>& dvec2) noexcept
{
	glUniform2d(glGetUniformLocation(m_id, uniformName.c_str()), dvec2.width, dvec2.height);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_dvec3(const std::string& uniformName, const dvec3& dvec3) noexcept
{
	glUniform3d(glGetUniformLocation(m_id, uniformName.c_str()), dvec3.x, dvec3.y, dvec3.z);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_dvec3(const std::string& uniformName, const Color<double>& dvec3) noexcept
{
	glUniform3d(glGetUniformLocation(m_id, uniformName.c_str()), dvec3.r, dvec3.g, dvec3.b);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_dvec4(const std::string& uniformName, const dvec4& dvec4) noexcept
{
	glUniform4d(glGetUniformLocation(m_id, uniformName.c_str()), dvec4.x, dvec4.y, dvec4.z, dvec4.w);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_dvec4(const std::string& uniformName, const Color<double>& dvec4) noexcept
{
	glUniform4d(glGetUniformLocation(m_id, uniformName.c_str()), dvec4.r, dvec4.g, dvec4.b, dvec4.a);
	return *this;
}

hgui::kernel::Shader& hgui::kernel::Shader::set_mat4(const std::string& uniformName, const glm::mat4& mat4) noexcept
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, uniformName.c_str()), 1, false, glm::value_ptr(mat4));
	return *this;
}

GLuint hgui::kernel::Shader::load_shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode)
{
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geometryShader = 0;

	const char* srcVertexShader = vertexShaderCode.c_str();
	const char* srcFragmentShader = fragmentShaderCode.c_str();

	glShaderSource(vertexShader, 1, &srcVertexShader, nullptr);
	glShaderSource(fragmentShader, 1, &srcFragmentShader, nullptr);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	if (!geometryShaderCode.empty())
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		const char* srcGeometryShader = geometryShaderCode.c_str();
		glShaderSource(geometryShader, 1, &srcGeometryShader, nullptr);
		glCompileShader(geometryShader);
	}

	const GLuint shaderProgram = glCreateProgram();

	try
	{
		check_compile_error(vertexShader, fragmentShader, geometryShader);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		if (geometryShader)
		{
			glAttachShader(shaderProgram, geometryShader);
		}
		glLinkProgram(shaderProgram);

		check_linking_error(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryShader)
		{
			glDeleteShader(geometryShader);
		}
	}
	catch (const std::runtime_error& e)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryShader)
		{
			glDeleteShader(geometryShader);
		}
		std::cout << e.what() << std::endl;
		throw;
	}

	return shaderProgram;
}

void hgui::kernel::Shader::check_compile_error(const GLuint vertexShader, const GLuint fragmentShader, const GLuint geometryShader)
{
	int vertexSuccess, fragmentSuccess, geometrySuccess;
	char infoLog[512];
	std::stringstream errorMessage;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
	if (geometryShader)
	{
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &geometrySuccess);
	}
	if (!vertexSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		errorMessage << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	if (!fragmentSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		errorMessage << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	if (geometryShader && !geometrySuccess)
	{
		glGetShaderInfoLog(geometryShader, 512, nullptr, infoLog);
		errorMessage << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	if (!errorMessage.str().empty())
	{
		throw std::runtime_error(errorMessage.str().c_str());
	}
}

void hgui::kernel::Shader::check_linking_error(const GLuint shaderProgram)
{
	int programSuccess;
	std::stringstream errorMessage;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);
	if (!programSuccess)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		errorMessage << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	if (!errorMessage.str().empty())
	{
		throw std::runtime_error(errorMessage.str().c_str());
	}
}
