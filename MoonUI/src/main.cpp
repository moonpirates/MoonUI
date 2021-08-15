#include <iostream>
#include "XmlParser/Lexer.h"
#include <Systems/CallbackService.h>
#include <Services/GlobalServiceLocator.h>
#include "View/Window.h"

int main(int argc, const char* argv[])
{
	Lexer lexer;
	XmlDoc xmlDoc = lexer.Parse("test.xml");
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << xmlDoc.GetDebugInfo();

	Window window = Window();

	return 0;
}
