#pragma once

#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Macros/Macros.h>
#include "ShaderSource.h"

class Shader
{
public:
	Shader() = default;

	Shader(const std::string& path);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1iv(const std::string& name, int count, const int* v);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	unsigned int GetUnformLocation(const std::string& name);

private:
	unsigned int id;
	std::string path;
	std::unordered_map<std::string, int> locationCache;

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	ShaderSource ParseShaderFile(const std::string& path);
};

