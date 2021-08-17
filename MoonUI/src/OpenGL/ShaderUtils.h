#pragma once

#include <iostream>
#include <GL/glew.h>
#include <Macros/Macros.h>

class ShaderUtils
{
public:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};

