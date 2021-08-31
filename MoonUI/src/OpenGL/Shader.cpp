#include "Shader.h"


Shader::Shader(const std::string& path) : id(0), path(path)
{
	ShaderSource shaderSource = ParseShaderFile(path);
	id = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::Bind() const
{
	glUseProgram(id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int location = GetUnformLocation(name);
	glUniform4f(location, v0, v1, v2, v3);
}

unsigned int Shader::GetUnformLocation(const std::string& name)
{
	if (locationCache.find(name) != locationCache.end())
	{
		return locationCache[name];
	}

	int location = glGetUniformLocation(id, name.c_str());
	if (location == -1)
	{
		LOG_ERROR("Could not find uniform '" << name << "' in shader '" << path << "'.");
	}

	locationCache[name] = location;

	return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shaderID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		char* message = new char[length];
		glGetShaderInfoLog(shaderID, length, &length, message);
		LOG_ERROR("Failed to compile shader!");
		std::cout << message << std::endl;
		delete[] message;

		glDeleteShader(shaderID);
		return 0;
	}

	return shaderID;
}

unsigned int Shader::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int programID = glCreateProgram();
	unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

ShaderSource Shader::ParseShaderFile(const std::string& path)
{
	std::ifstream stream(path);
	std::stringstream stringStream[2];
	std::string line;
	int index = -1;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				index = 0;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				index = 1;
			}
		}
		else if (index >= 0)
		{
			stringStream[index] << line << '\n';
		}

	}

	return { stringStream[0].str(), stringStream[1].str() };
}
