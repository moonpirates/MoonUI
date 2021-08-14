#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <list>
#include <string>


namespace moonpirates
{
	class XmlElement
	{
	public:
		std::string Markup;
		std::string Tag;
		std::map<std::string, std::string> Attributes;
		std::string Content;
		std::shared_ptr<XmlElement> Parent;
		std::list<std::shared_ptr<XmlElement>> Children;
		int ID = 0;

		XmlElement(std::shared_ptr<XmlElement> parent);
		std::string GetDebugInfo();
		void AddChild(std::shared_ptr<XmlElement> child);
		void RemoveChild(std::shared_ptr<XmlElement> child);

	private:
		inline static int nextID = 0;
	};
}
