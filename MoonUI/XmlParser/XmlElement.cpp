#include "XmlElement.hpp"

using namespace moonpirates;

XmlElement::XmlElement(std::shared_ptr<XmlElement> parent) : Parent(parent), ID(nextID++)
{
	Children = std::list<std::shared_ptr<XmlElement>>();
}

void XmlElement::AddChild(std::shared_ptr<XmlElement> child)
{
	Children.push_back(child);
}

void XmlElement::RemoveChild(std::shared_ptr<XmlElement> child)
{
    Children.remove(child);
}

std::string XmlElement::GetDebugInfo()
{
    std::string info = "Tag: '" + Tag + "'";
    
    if (Content != "")
    {
        info +=  " | Content: '" + Content + "'";
    }
    
    if (Parent != nullptr)
    {
        info += " | Parent '" + Parent->Tag + "'";
    }
	
	info += " | Children: " + std::to_string(Children.size()) + " | ID: " + std::to_string(ID);
    
    return info;
}