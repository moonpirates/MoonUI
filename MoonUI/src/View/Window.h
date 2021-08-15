#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Systems/Renderable.h>
#include <Systems/CallbackService.h>
#include <Services/GlobalServiceLocator.h>
#include <Macros/Macros.h>

class Window : public Utils::Renderable
{
public:
	Window();
	~Window();
	void Render() override;
	void Stop();
private:
	Utils::CallbackService& callbackService;
	GLFWwindow* window;
};

