#include <iostream>
#include "View/Window.h"
#include "Example/TestSceneDecorator.h"

int main(int argc, const char* argv[])
{
	Window window;
	TestSceneDecorator testSceneDecorator;

	window.Start();

	return 0;
}
