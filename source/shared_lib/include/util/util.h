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

#ifndef _SHARED_UTIL_UTIL_H_
#define _SHARED_UTIL_UTIL_H_

#include <string>




namespace Shared{ namespace Util{

const std::string sharedLibVersionString= "v0.4.1";

//string fcs
std::string lastDir(const std::string &s);
std::string lastFile(const std::string &s);
std::string cutLastFile(const std::string &s);
std::string cutLastExt(const std::string &s);
std::string ext(const std::string &s);
std::string replaceBy(const std::string &s, char c1, char c2);
std::string toLower(const std::string &s);
void copyStringToBuffer(char *buffer, int bufferSize, const std::string& s);

//numeric fcs
int clamp(int value, int min, int max);
float clamp(float value, float min, float max);
float saturate(float value);
int round(float f);

//misc
bool fileExists(const std::string &path);

template<typename T> 
void deleteValues(T beginIt, T endIt){
	for(T it= beginIt; it!=endIt; ++it){
		delete *it;
	}
}

template<typename T> 
void deleteMapValues(T beginIt, T endIt){
	for(T it= beginIt; it!=endIt; ++it){
		delete it->second;
	}
}

}}//end namespace

#endif
