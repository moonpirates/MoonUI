#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Systems/Renderable.h>
#include <Systems/CallbackService.h>
#include <Services/GlobalServiceLocator.h>
#include <Macros/Macros.h>
#include "../OpenGL/ShaderUtils.h"
#include "../OpenGL/OpenGLDebug.h"
#include "../OpenGL/VertexBuffer.h"
#include "../OpenGL/IndexBuffer.h"
#include "../OpenGL/VertexArray.h"

class Window : public Utils::Renderable
{
public:
	Window();
	~Window();
	void Render() override;
	void Stop();
private:
	VertexBuffer* vertexBuffer;
	VertexArray* vertexArray;
	IndexBuffer* indexBuffer;
	unsigned int shaderID;
	unsigned int vertexArrayObjectID;

	Utils::CallbackService& callbackService;
	GLFWwindow* window;
};

