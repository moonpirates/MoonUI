#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <regex>
#include "XmlDoc.hpp"
#include "XmlElement.hpp"

namespace moonpirates
{
    class Lexer
    {
    public:
        Lexer();
        moonpirates::XmlDoc Parse(std::string path);
    private:
        const char NODE_OPENING_CHAR = '<';
        const char NODE_CLOSING_CHAR = '>';
        
        std::string ReadFile(std::string path);
        std::string& TrimLeft(std::string& s);
        std::string& TrimRight(std::string& s);
        std::string& Trim(std::string& s);
        std::string& Sanitize(std::string& s);
        void ParseMarkup(std::string markup, std::shared_ptr<XmlElement> element);
    };

}
