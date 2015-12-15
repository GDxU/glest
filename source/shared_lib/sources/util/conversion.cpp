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

#include "conversion.h"

#include <stdexcept>
#include <cstdio>
#include <cstdlib>





namespace Glest {

const int strSize = 256;

bool strToBool(const std::string &s){
	if (s=="0" || s=="false"){
		return false;
	}
	if (s=="1" || s=="true"){
		return true;
	}
	throw std::runtime_error("Error converting std::string to bool, expected 0 or 1, found: " + s);
}

int strToInt(const std::string &s){
	char *endChar;
	int intValue= strtol(s.c_str(), &endChar, 10);
	
	if(*endChar!='\0'){
		throw std::runtime_error("Error converting from std::string to int, found: "+s);
	}

	return intValue;
}


float strToFloat(const std::string &s){
	char *endChar;
	float floatValue= static_cast<float>(strtod(s.c_str(), &endChar));
	
	if(*endChar!='\0'){
		throw std::runtime_error("Error converting from std::string to float, found: "+s);
	}

	return floatValue;
}

bool strToBool(const std::string &s, bool *b){
	if (s=="0" || s=="false"){
		*b= false;
		return true;
	}
	if (s=="1" || s=="true"){
		*b= true;
		return true;
	}
     
	return false;
}

bool strToInt(const std::string &s, int *i){
	char *endChar;
	*i= strtol(s.c_str(), &endChar, 10);
	
	if(*endChar!='\0'){
		return false;
	}
	return true;
}

bool strToFloat(const std::string &s, float *f){
	char *endChar;
	*f= static_cast<float>(strtod(s.c_str(), &endChar));
	
	if(*endChar!='\0'){
		return false;
	}
	return true;
}

std::string boolToStr(bool b){
	if(b){
		return "1";
	}
	else{
		return "0";
	}
}

std::string intToStr(int i){
	char str[strSize];
	sprintf(str, "%d", i);
	return str; 
}

std::string intToHex(int i){
	char str[strSize];
	sprintf(str, "%x", i);
	return str;
}

std::string floatToStr(float f){
	char str[strSize];
	sprintf(str, "%.2f", f);
	return str; 
}

std::string doubleToStr(double d){
	char str[strSize];
	sprintf(str, "%.2f", d);
	return str; 
}


}//end namespace
