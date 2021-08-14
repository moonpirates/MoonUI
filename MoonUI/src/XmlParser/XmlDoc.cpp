#include "XmlDoc.h"

XmlDoc::XmlDoc()
{
	Root = std::make_shared<XmlElement>(nullptr);
}

std::string XmlDoc::GetDebugInfo()
{
	std::string debugInfo = "";
	RecursiveLogElement(Root, 0, debugInfo);

	return debugInfo;
}

void XmlDoc::RecursiveLogElement(std::shared_ptr<XmlElement> element, int depth, std::string& debugInfo)
{
	std::string tabs = std::string(depth, '\t');
	debugInfo += tabs + element->GetDebugInfo() + "\n";

	if (element->Children.size() > 0)
	{
		depth++;
		std::list<std::shared_ptr<XmlElement>>::iterator it;
		for (it = element->Children.begin(); it != element->Children.end(); it++)
		{
			RecursiveLogElement(*it, depth, debugInfo);
		}
		depth--;
	}
}
