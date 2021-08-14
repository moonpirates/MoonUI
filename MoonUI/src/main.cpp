#include <iostream>
#include "XmlParser/Lexer.h"

int main(int argc, const char* argv[])
{
	Lexer lexer;
	XmlDoc xmlDoc = lexer.Parse("test.xml");
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << xmlDoc.GetDebugInfo();
	return 0;
}
