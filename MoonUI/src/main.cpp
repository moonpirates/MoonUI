#include <iostream>
#include "XmlParser/Lexer.h"
#include <Systems/CallbackService.h>
#include <Services/GlobalServiceLocator.h>
#include "View/Canvas.h"

int main(int argc, const char* argv[])
{
	Lexer lexer;
	XmlDoc xmlDoc = lexer.Parse("test.xml");
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << xmlDoc.GetDebugInfo();

	Utils::CallbackService callbackService = Utils::GlobalServiceLocator::Get<Utils::CallbackService>();

	Canvas canvas = Canvas();
	callbackService.AddRenderable(canvas);

	callbackService.Start();

	return 0;
}
