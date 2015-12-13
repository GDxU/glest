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

#ifndef _SHARED_XML_XMLPARSER_H_
#define _SHARED_XML_XMLPARSER_H_

#include <string>
#include <vector>
#include "tinyxml2.h"



namespace Shared{ namespace Xml{

const int strSize= 256;

class XmlIo;
class XmlTree;
class XmlNode;
class XmlAttribute;
	

// =====================================================
//	class XmlTree
// =====================================================

class XmlTree
{
private:
    tinyxml2::XMLDocument doc;
    XmlNode* root;

private:
	XmlTree(XmlTree&);
	void operator =(XmlTree&);

public:
	XmlTree();
	~XmlTree();
	
	void init(const std::string &name);
	void load(const std::string &path);
	void save(const std::string &path);
	
    XmlNode *getRootNode() const;
};

// =====================================================
//	class XmlNode
// =====================================================

class XmlNode
{
private:
    std::string name;
    std::string text;
	std::vector<XmlNode*> children;
    std::vector<XmlAttribute*> attributes;

private:
	XmlNode(XmlNode&);
	void operator =(XmlNode&);

public:
    XmlNode(const tinyxml2::XMLElement* node);
    XmlNode(const std::string &name);
	~XmlNode();

    const std::string &getName() const	{ return name; }
	int getChildCount() const		{return children.size();}
	int getAttributeCount() const	{return attributes.size();}
    const std::string &getText() const	{ return text; }

	XmlAttribute *getAttribute(int i) const;
    XmlAttribute *getAttribute(const std::string &name) const;
	XmlNode *getChild(int i) const;
    XmlNode *getChild(const std::string &childName, int childIndex = 0) const;
	XmlNode *getParent() const;


    XmlNode *addChild(const std::string &name);
    XmlAttribute *addAttribute(const std::string &name, const std::string &value);

    //XERCES_CPP_NAMESPACE::DOMElement *buildElement(XERCES_CPP_NAMESPACE::DOMDocument *document) const;

private:
    std::string getTreeString() const;
};

// =====================================================
//	class XmlAttribute
// =====================================================

class XmlAttribute{
private:
    std::string value;
    std::string name;

private:
	XmlAttribute(XmlAttribute&);
	void operator =(XmlAttribute&);

public:
    //XmlAttribute(XERCES_CPP_NAMESPACE::DOMNode *attribute);
    XmlAttribute(const std::string &name, const std::string &value);

public:
    const std::string &getName() const	{ return name; }
    const std::string &getValue() const	{ return value; }

	bool getBoolValue() const;
	int getIntValue() const;		
	int getIntValue(int min, int max) const;
	float getFloatValue() const;		
	float getFloatValue(float min, float max) const;
    const std::string &getRestrictedValue() const;
};


}}//end namespace

#endif
