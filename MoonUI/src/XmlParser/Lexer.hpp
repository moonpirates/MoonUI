#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <regex>
#include "XmlDoc.hpp"
#include "XmlElement.hpp"
#include <Macros/Macros.h>

namespace moonpirates
{
	class Lexer
	{
	public:
		Lexer();
		moonpirates::XmlDoc Parse(std::string path);
	private:
		std::string ReadFile(std::string path);
		void TrimLeft(std::string& s);
		void TrimRight(std::string& s);
		void Trim(std::string& s);
		void Sanitize(std::string& s);
		void ParseMarkup(std::string markup, std::shared_ptr<XmlElement> element);
	};

}
