#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <regex>
#include <Macros/Macros.h>
#include "XmlDoc.h"
#include "XmlElement.h"

class Lexer
{
public:
	XmlDoc Parse(std::string path);
private:
	std::string ReadFile(std::string path);
	void TrimLeft(std::string& s);
	void TrimRight(std::string& s);
	void Trim(std::string& s);
	void Sanitize(std::string& s);
	void ParseMarkup(std::string markup, std::shared_ptr<XmlElement> element);
};
