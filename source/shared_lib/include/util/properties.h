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

#ifndef _SHARED_UTIL_PROPERTIES_H_
#define _SHARED_UTIL_PROPERTIES_H_

#include <string>
#include <map>
#include <vector>










namespace Shared{ namespace Util{

// =====================================================
//	class Properties
//
///	ini-like file loader
// =====================================================

class Properties{
private:
	static const int maxLine= 1024;

public:	
    typedef std::pair<std::string, std::string> PropertyPair;
    typedef std::map<std::string, std::string> PropertyMap;
	typedef std::vector<PropertyPair> PropertyVector;
	
private:
	PropertyVector propertyVector;
	PropertyMap propertyMap;
	std::string path;

public:
	void clear();
	void load(const std::string &path);
	void save(const std::string &path);

	int getPropertyCount()	{return propertyVector.size();}
	std::string getKey(int i)	{return propertyVector[i].first;}
	std::string getString(int i)	{return propertyVector[i].second;}

	bool getBool(const std::string &key) const;
	int getInt(const std::string &key) const;
	int getInt(const std::string &key, int min, int max) const;
	float getFloat(const std::string &key) const;
	float getFloat(const std::string &key, float min, float max) const;
	const std::string &getString(const std::string &key) const;

	void setInt(const std::string &key, int value);
	void setBool(const std::string &key, bool value);
	void setFloat(const std::string &key, float value);
	void setString(const std::string &key, const std::string &value);

	std::string toString();


};

}}//end namespace

#endif
