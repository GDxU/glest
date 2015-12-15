// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2001-2008 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#include "xml_parser.h"

#include <fstream>
#include <stdexcept>

#include "conversion.h"

// #include <xercesc/dom/DOM.hpp>
// #include <xercesc/util/PlatformUtils.hpp>
// #include <xercesc/framework/LocalFileFormatTarget.hpp>

#include "tinyxml2.h"






namespace Glest {



// =====================================================
//	class XmlTree
// =====================================================

XmlTree::XmlTree(){
    root = nullptr;
}

XmlTree::~XmlTree(){
    if (root)
        delete root;
}

void XmlTree::init(const std::string &name)
{
	//this->rootNode= new XmlNode(name);
}

void XmlTree::load(const std::string &path)
{
    tinyxml2::XMLDocument doc;

    tinyxml2::XMLError err = doc.LoadFile(path.c_str());

    if (err != tinyxml2::XML_SUCCESS)
        throw std::runtime_error("Can not parse XML: " + path);

    root = new XmlNode(doc.FirstChildElement());
}

void XmlTree::save(const std::string &path){

    tinyxml2::XMLError err = doc.SaveFile(path.c_str());

    if (err != tinyxml2::XML_SUCCESS)
        throw std::runtime_error("Can not Save : " + path);

}



XmlNode *XmlTree::getRootNode() const
{
    return root;
}

// =====================================================
//	class XmlNode
// =====================================================

XmlNode::XmlNode(const tinyxml2::XMLElement* node)
{
    const tinyxml2::XMLAttribute* attr = node->FirstAttribute();

	this->name = node->Name();
	const char* textVa = node->GetText();
	if (textVa)
		this->text = textVa;

    while (attr)
    {
        attributes.push_back(new XmlAttribute(attr->Name(), attr->Value()));

        attr = attr->Next();
    }
    const tinyxml2::XMLElement* child = node->FirstChildElement();
    while (child)
    {
        children.push_back(new XmlNode(child));

        child = child->NextSiblingElement();
    }

}

XmlNode::XmlNode(const std::string &name){
	this->name= name;
}

XmlNode::~XmlNode(){
	for(int i=0; i<children.size(); ++i){
		delete children[i];
	}
	for(int i=0; i<attributes.size(); ++i){
		delete attributes[i];
	}
}

XmlAttribute *XmlNode::getAttribute(int i) const{
	if(i>=attributes.size()){
		throw std::runtime_error(getName()+" node doesn't have "+intToStr(i)+" attributes");
	}
	return attributes[i];
}
	
XmlAttribute *XmlNode::getAttribute(const std::string &name) const{
	for(int i=0; i<attributes.size(); ++i){
		if(attributes[i]->getName()==name){
			return attributes[i];
		}
	}
	throw std::runtime_error("\"" + getName() + "\" node doesn't have a attribute named \"" + name + "\"");
}

XmlNode *XmlNode::getChild(int i) const {
	if(i>=children.size())
		throw std::runtime_error("\"" + getName()+"\" node doesn't have "+intToStr(i+1)+" children");
	return children[i];
}


XmlNode *XmlNode::getChild(const std::string &childName, int i) const{
	if(i>=children.size()){
		throw std::runtime_error("\"" + name + "\" node doesn't have "+intToStr(i+1)+" children named \"" + childName + "\"\n\nTree: "+getTreeString());
	}

	int count= 0;
	for(int j=0; j<children.size(); ++j){
		if(children[j]->getName()==childName){
			if(count==i){
				return children[j];
			}
			count++;
		}
	}

	throw std::runtime_error("Node \""+getName()+"\" doesn't have "+intToStr(i+1)+" children named  \""+childName+"\"\n\nTree: "+getTreeString());
}

XmlNode *XmlNode::addChild(const std::string &name){
	XmlNode *node= new XmlNode(name);
	children.push_back(node);
	return node;
}

XmlAttribute *XmlNode::addAttribute(const std::string &name, const std::string &value){
	XmlAttribute *attr= new XmlAttribute(name, value);
	attributes.push_back(attr);
	return attr;
}
// 
// DOMElement *XmlNode::buildElement(DOMDocument *document) const{
// 	XMLCh str[strSize];
// 	XMLString::transcode(name.c_str(), str, strSize-1);
// 
// 	DOMElement *node= document->createElement(str);
// 
// 	for(int i=0; i<attributes.size(); ++i){
//         XMLString::transcode(attributes[i]->getName().c_str(), str, strSize-1);
// 		DOMAttr *attr= document->createAttribute(str);
// 		
// 		XMLString::transcode(attributes[i]->getValue().c_str(), str, strSize-1);
// 		attr->setValue(str);
// 
// 		node->setAttributeNode(attr);
// 	}
// 
// 	for(int i=0; i<children.size(); ++i){
// 		node->appendChild(children[i]->buildElement(document));
// 	}
// 
// 	return node;
// }

std::string XmlNode::getTreeString() const{
	std::string str;

	str+= getName();

	if(!children.empty()){
		str+= " (";
		for(int i=0; i<children.size(); ++i){
			str+= children[i]->getTreeString();
			str+= " ";
		}
		str+=") ";
	}

	return str;
}

// =====================================================
//	class XmlAttribute
// =====================================================
// 
// XmlAttribute::XmlAttribute(XERCES_CPP_NAMESPACE::DOMNode *attribute){
// 	char str[strSize];
// 
// 	XMLString::transcode(attribute->getNodeValue(), str, strSize-1);
// 	value= str;
// 
// 	XMLString::transcode(attribute->getNodeName(), str, strSize-1);
// 	name= str;
// }

XmlAttribute::XmlAttribute(const std::string &name, const std::string &value){
	this->name= name;
	this->value= value;
}

bool XmlAttribute::getBoolValue() const{
	if(value=="true"){
		return true;
	}
	else if(value=="false"){
		return false;
	}
	else{
		throw std::runtime_error("Not a valid bool value (true or false): " +getName()+": "+ value);
	}
}

int XmlAttribute::getIntValue() const{
	return strToInt(value);
}

int XmlAttribute::getIntValue(int min, int max) const{
	int i= strToInt(value);
	if(i<min || i>max){
		throw std::runtime_error("Xml Attribute int out of range: " + getName() + ": " + value);
	}
	return i;
}

float XmlAttribute::getFloatValue() const{
	return strToFloat(value);
}

float XmlAttribute::getFloatValue(float min, float max) const{
	float f= strToFloat(value);
	if(f<min || f>max){
		throw std::runtime_error("Xml attribute float out of range: " + getName() + ": " + value);
	}
	return f;
}

const std::string &XmlAttribute::getRestrictedValue() const
{
	const std::string allowedCharacters = "abcdefghijklmnopqrstuvwxyz1234567890._-/";

	for(int i= 0; i<value.size(); ++i){
		if(allowedCharacters.find(value[i])==std::string::npos){
			throw std::runtime_error(
				std::string("The std::string \"" + value + "\" contains a character that is not allowed: \"") + value[i] +
				"\"\nFor portability reasons the only allowed characters in this field are: " + allowedCharacters);
		}
	}
		
	return value;
}

}//end namespace
