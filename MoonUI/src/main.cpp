#include <iostream>
#include "Lexer.hpp"

using namespace moonpirates;



int main(int argc, const char * argv[])
{
    Lexer lexer;
    XmlDoc xmlDoc = lexer.Parse("test.xml");
	
//   std::string strr("root toot");
//
//   std::regex rgx("([a-z]+)");
//   std::smatch match;
//
//   while (std::regex_search(strr, match, rgx)) {
//	  std::cout << "match: " << match[0] << std::endl;
//	  strr = match.suffix();
//   }

	
//	std::cout << "--------------------------------------------" << std::endl;
//	std::cout << xmlDoc.GetDebugInfo();
    return 0;
}
