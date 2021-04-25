#include "Lexer.hpp"

using namespace moonpirates;

Lexer::Lexer()
{
}

XmlDoc Lexer::Parse(std::string path)
{
	std::string xml = ReadFile(path);
    std::cout << xml << std::endl << "--------------------------------------------" << std::endl;
    
	XmlDoc xmlDoc;
	
    std::string buffer;
    int depth = -1;
    bool readingMarkup = false;
    bool readingContent = false;
    
    std::shared_ptr<XmlElement> currentElement = xmlDoc.Root;
    std::string::size_type numChars = xml.length();
    
    for (int i = 0; i < numChars; i++)
    {
        char c = xml[i];

        bool lastChar = i == numChars - 1;
        
        bool openingMarkup = !lastChar && xml[i] == '<' && xml[i + 1] != '/';
        bool closingContent = !lastChar && xml[i] == '<' && xml[i + 1] == '/';
        bool closingEmptyElement = !lastChar && xml[i] == '/' && xml[i + 1] == '>';
        
        if (openingMarkup || closingContent || closingEmptyElement)
        {
            i++;
            c = xml[i];
        }
        
        if (openingMarkup)
        {
            std::shared_ptr<XmlElement> newElement = std::make_shared<XmlElement>(currentElement);
			
			if (currentElement != nullptr)
			{
				currentElement->AddChild(newElement);
			}
			
			currentElement = newElement;
			
            depth++;
            readingMarkup = true;
        }
        else if (closingContent)
        {
            buffer = Sanitize(buffer);
            
            std::string tabs = std::string(depth, '\t');
            currentElement->Content = buffer;
            std::cout << tabs << "[" << depth << "] " << currentElement->GetDebugInfo() << std::endl;
            
            currentElement = currentElement->Parent;
            depth--;
            readingContent = false;
            buffer = "";
        }
        else if (closingEmptyElement)
        {
            buffer = Sanitize(buffer);
            std::string tabs = std::string(depth, '\t');
            currentElement->Markup = buffer;
            ParseMarkup(buffer, currentElement);
            
            std::cout << tabs << "[" << depth << "] " << currentElement->GetDebugInfo() << std::endl;
            
            currentElement = currentElement->Parent;
            depth--;
            
            readingMarkup = false;
            buffer = "";
        }
        
        if (readingMarkup)
        {
            if (c == '>')
            {
                readingMarkup = false;
                readingContent = true;
                buffer = Sanitize(buffer);
                currentElement->Markup = buffer;
                ParseMarkup(buffer, currentElement);
                buffer = "";
            }
            else
            {
                buffer += c;
            }
        }
        else if (readingContent)
        {
            buffer += c;
        }
    }
	
    return xmlDoc;
}

std::string Lexer::ReadFile(std::string path)
{
    std::string output;
    std::ifstream fileStream(path);
    std::stringstream stringStream;
    
    if (fileStream.is_open())
    {
        stringStream << fileStream.rdbuf();
        return stringStream.str();
    }
    else
    {
        std::cout << "Cannot open file at path: " << path << std::endl;
        return "";
    }
}

std::string& Lexer::TrimLeft(std::string& s)
{
    s.erase(0, s.find_first_not_of(" "));
    return s;
}

std::string& Lexer::TrimRight(std::string& s)
{
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

std::string& Lexer::Trim(std::string& s)
{
    return TrimLeft(TrimRight(s));
}

std::string& Lexer::Sanitize(std::string& s)
{
    std::regex sanitizeRegex("\n+|\t+");
    s = std::regex_replace(s, sanitizeRegex, "");
    
    return Trim(s);
}

void Lexer::ParseMarkup(std::string markup, std::shared_ptr<XmlElement> element)
{
    element->Markup = markup;
    
    std::string::size_type position = markup.find(' ');
    
    element->Tag = markup.substr(0, position);

    if (position != std::string::npos)
    {
        std::string attributesString = markup.substr(position);
    }
}
