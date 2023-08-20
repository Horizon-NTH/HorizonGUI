#include <hgui/header/Shader.h>

hgui::kernel::Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader) :
	m_id(load_shader(vertexShader, fragmentShader, geometryShader))
{
}

hgui::kernel::Shader::~Shader()
{
	glDeleteProgram(m_id);
}

const hgui::kernel::Shader& hgui::kernel::Shader::use() const
{
	glUseProgram(m_id);
	return *this;
}

const GLuint hgui::kernel::Shader::get_id() const
{
	return m_id;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_float(const std::string& uniformName, float f) const
{
	glUniform1f(glGetUniformLocation(m_id, uniformName.c_str()), f);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_int(const std::string& uniformName, int i) const
{
	glUniform1i(glGetUniformLocation(m_id, uniformName.c_str()), i);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_vec2(const std::string& uniformName, const vec2& vec2) const
{
	glUniform2f(glGetUniformLocation(m_id, uniformName.c_str()), vec2.x, vec2.y);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_vec3(const std::string& uniformName, const vec3& vec3) const
{
	glUniform3f(glGetUniformLocation(m_id, uniformName.c_str()), vec3.x, vec3.y, vec3.z);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_vec4(const std::string& uniformName, const vec4& vec4) const
{
	glUniform4f(glGetUniformLocation(m_id, uniformName.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_double(const std::string& uniformName, double d) const
{
	glUniform1d(glGetUniformLocation(m_id, uniformName.c_str()), d);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_dvec2(const std::string& uniformName, const dvec2& dvec2) const
{
	glUniform2d(glGetUniformLocation(m_id, uniformName.c_str()), dvec2.x, dvec2.y);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_dvec3(const std::string& uniformName, const dvec3& dvec3) const
{
	glUniform3d(glGetUniformLocation(m_id, uniformName.c_str()), dvec3.x, dvec3.y, dvec3.z);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_dvec4(const std::string& uniformName, const dvec4& dvec4) const
{
	glUniform4d(glGetUniformLocation(m_id, uniformName.c_str()), dvec4.x, dvec4.y, dvec4.z, dvec4.w);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_mat4(const std::string& uniformName, const glm::mat4& mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, uniformName.c_str()), 1, false, glm::value_ptr(mat4));
	return *this;
}

const GLuint hgui::kernel::Shader::load_shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode, const std::string& geometryShaderCode)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geometryShader = 0;

	const char* srcVertexShader = vertexShaderCode.c_str();
	const char* srcFragmentShader = fragmentShaderCode.c_str();

	glShaderSource(vertexShader, 1, &srcVertexShader, NULL);
	glShaderSource(fragmentShader, 1, &srcFragmentShader, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	if (!geometryShaderCode.empty())
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		const char* srcGeometryShader = geometryShaderCode.c_str();
		glShaderSource(geometryShader, 1, &srcGeometryShader, NULL);
		glCompileShader(geometryShader);
	}

	GLuint shaderProgram = glCreateProgram();

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
	catch (const std::exception& e)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryShader)
		{
			glDeleteShader(geometryShader);
		}
		std::cout << e.what() << std::endl;
		throw e;
	}

	return shaderProgram;
}

void hgui::kernel::Shader::check_compile_error(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) const
{
	int  vertex_success, fragment_success, geometry_success;
	char infoLog[512];
	std::stringstream errorMessage;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_success);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_success);
	if (geometryShader)
	{
		glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &geometry_success);
	}
	if (!vertex_success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		errorMessage << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	if (!fragment_success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		errorMessage << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	if (geometryShader && !geometry_success)
	{
		glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
		errorMessage << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	if (!errorMessage.str().empty())
	{
		throw std::runtime_error(errorMessage.str().c_str());
	}
}

void hgui::kernel::Shader::check_linking_error(GLuint shaderProgram) const
{
	int programSuccess;
	char infoLog[512];
	std::stringstream errorMessage;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);
	if (!programSuccess)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		errorMessage << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	if (!errorMessage.str().empty())
	{
		throw std::runtime_error(errorMessage.str().c_str());
	}
}
