#include <hgui/header/Shader.h>

hgui::kernel::Shader::Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) :
	m_id(load_shader(vertexShaderCode, fragmentShaderCode))
{
}

hgui::kernel::Shader::~Shader()
{
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

const hgui::kernel::Shader& hgui::kernel::Shader::set_1f(const char* uniformName, float f) const
{
	glUniform1f(glGetUniformLocation(m_id, uniformName), f);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_1i(const char* uniformName, int i) const
{
	glUniform1i(glGetUniformLocation(m_id, uniformName), i);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_vec2f(const char* uniformName, glm::vec2 vec2) const
{
	glUniform2f(glGetUniformLocation(m_id, uniformName), vec2.x, vec2.y);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_vec3f(const char* uniformName, glm::vec3 vec3) const
{
	glUniform3f(glGetUniformLocation(m_id, uniformName), vec3.x, vec3.y, vec3.z);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_vec4f(const char* uniformName, glm::vec4 vec4) const
{
	glUniform4f(glGetUniformLocation(m_id, uniformName), vec4.x, vec4.y, vec4.z, vec4.w);
	return *this;
}

const hgui::kernel::Shader& hgui::kernel::Shader::set_mat4(const char* uniformName, glm::mat4 mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, uniformName), 1, false, glm::value_ptr(mat4));
	return *this;
}

const GLuint hgui::kernel::Shader::load_shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER),
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER),
		shaderProgram = glCreateProgram();
	const char* srcVertexShader = vertexShaderCode.c_str(),
		* srcFragmentShader = fragmentShaderCode.c_str();

	glShaderSource(vertexShader, 1, &srcVertexShader, NULL);
	glShaderSource(fragmentShader, 1, &srcFragmentShader, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	try
	{
		check_compile_error(vertexShader, fragmentShader);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		check_linking_error(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(vertexShader);
	}
	catch (const std::exception& e)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(vertexShader);
		std::cout << e.what() << std::endl;
		throw e;
	}

	return shaderProgram;
}

void hgui::kernel::Shader::check_compile_error(GLuint vertexShader, GLuint fragmentShader) const
{
	int  vertex_success, fragment_success;
	char infoLog[512];
	std::stringstream errorMessage;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertex_success);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_success);
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
