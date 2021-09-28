#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Systems/Renderable.h>
#include <Systems/CallbackService.h>
#include <Services/GlobalServiceLocator.h>
#include <Macros/Macros.h>

#include "../OpenGL/GLEW.h"
#include "../OpenGL/GLFW.h"	
#include "../OpenGL/Shader.h"
#include "../OpenGL/OpenGLDebug.h"
#include "../OpenGL/VertexBuffer.h"
#include "../OpenGL/IndexBuffer.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/Renderer.h"
#include "../OpenGL/Texture.h"
#include "../OpenGL/Vertex.h"
#include "../OpenGL/MeshGenerator.h"
#include "../OpenGL/RenderService.h"

class Window : public Utils::Renderable, Utils::Updatable
{
public:
	Window();
	~Window();
	void Update() override;
	void PreRender() override;
	void PostRender() override;
	void Start();
	void Stop();
	int GetWindowWidth();
	int GetWindowHeight();

private:
	Renderer* renderer;

	int windowWidth;
	int windowHeight;

	Utils::CallbackService& callbackService;
	GLFWwindow* window;
	
	void UpdateWindowSize();
};

