#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Systems/Renderable.h>
#include <Systems/CallbackService.h>
#include <Services/GlobalServiceLocator.h>
#include <Macros/Macros.h>
#include "../OpenGL/Shader.h"
#include "../OpenGL/OpenGLDebug.h"
#include "../OpenGL/VertexBuffer.h"
#include "../OpenGL/IndexBuffer.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Renderer.h"
#include "../OpenGL/Texture.h"

class Window : public Utils::Renderable
{
public:
	Window();
	~Window();
	void Render() override;
	void Stop();
private:
	Renderer* renderer;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;
	Shader* shader;
	Texture* texture;

	Utils::CallbackService& callbackService;
	GLFWwindow* window;
};

