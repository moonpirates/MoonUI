#include "ShaderUtils.h"

unsigned int ShaderUtils::CompileShader(unsigned int type, const std::string& source)
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

unsigned int ShaderUtils::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
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
