#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "XmlElement.h"

class XmlDoc
{
public:
	XmlDoc();
	std::shared_ptr<XmlElement> Root;
	std::string GetDebugInfo();
private:
	void RecursiveLogElement(std::shared_ptr<XmlElement> element, int depth, std::string& debugInfo);
};
