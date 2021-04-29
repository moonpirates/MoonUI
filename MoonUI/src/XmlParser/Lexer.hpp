#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <regex>
#include "XmlDoc.hpp"
#include "XmlElement.hpp"
#include "Macros.h"

namespace moonpirates
{
    class Lexer
    {
    public:
        Lexer();
        moonpirates::XmlDoc Parse(std::string path);
    private:
        std::string ReadFile(std::string path);
        std::string& TrimLeft(std::string& s);
        std::string& TrimRight(std::string& s);
        std::string& Trim(std::string& s);
        std::string& Sanitize(std::string& s);
        void ParseMarkup(std::string markup, std::shared_ptr<XmlElement> element);
    };

}
