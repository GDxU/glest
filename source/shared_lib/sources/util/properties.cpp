// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2001-2007 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#include "properties.h"

#include <fstream>
#include <stdexcept>
#include <cstring>

#include "conversion.h"




namespace Shared{ namespace Util{

// =====================================================
//	class Properties
// =====================================================

void Properties::load(const std::string &path){
    std::ifstream fileStream;
	char lineBuffer[maxLine];
	std::string line, key, value;
	int pos;

	this->path= path;

    fileStream.open(path.c_str(), std::ios_base::in);
	if(fileStream.fail()){
		throw std::runtime_error("Can't open propertyMap file: " + path);
	}

	propertyMap.clear();
	while(!fileStream.eof()){
		fileStream.getline(lineBuffer, maxLine);
		lineBuffer[maxLine-1]='\0';
		
		//process line if it it not a comment
		if(lineBuffer[0]!=';'){
			
			// gracefully handle win32 \r\n line endings
			size_t len= strlen(lineBuffer);
   			if(len > 0 && lineBuffer[len-1] == '\r'){
				lineBuffer[len-1]= 0;
			}

			line= lineBuffer;
			pos= line.find('=');
		
            if (pos != std::string::npos){
				key= line.substr(0, pos);
				value= line.substr(pos+1);
				propertyMap.insert(PropertyPair(key, value));
				propertyVector.push_back(PropertyPair(key, value));
			}
		}
	}

	fileStream.close();
}
	
void Properties::save(const std::string &path){
    std::ofstream fileStream;

    fileStream.open(path.c_str(), std::ios_base::out | std::ios_base::trunc);

	fileStream << "; === propertyMap File === \n";	
	fileStream << '\n';

	for(PropertyMap::iterator pi= propertyMap.begin(); pi!=propertyMap.end(); ++pi){
		fileStream << pi->first << '=' << pi->second << '\n';
	}

	fileStream.close();
}

void Properties::clear(){
	propertyMap.clear();
	propertyVector.clear();
}

bool Properties::getBool(const std::string &key) const{
	try{
		return strToBool(getString(key));
	}
    catch (std::exception &e){
		throw std::runtime_error("Error accessing value: " + key + " in: " + path+"\n" + e.what());
	}
}

int Properties::getInt(const std::string &key) const{
	try{
		return strToInt(getString(key));
	}
    catch (std::exception &e){
		throw std::runtime_error("Error accessing value: " + key + " in: " + path + "\n" + e.what());
	}
}

int Properties::getInt(const std::string &key, int min, int max) const{
	int i= getInt(key);
	if(i<min || i>max){
		throw std::runtime_error("Value out of range: " + key + ", min: " + intToStr(min) + ", max: " + intToStr(max));
	}
	return i;
}

float Properties::getFloat(const std::string &key) const{
	try{
		return strToFloat(getString(key));
	}
    catch (std::exception &e){
		throw std::runtime_error("Error accessing value: " + key + " in: " + path + "\n" + e.what());
	}
}

float Properties::getFloat(const std::string &key, float min, float max) const{
	float f= getFloat(key);
	if(f<min || f>max){
		throw std::runtime_error("Value out of range: " + key + ", min: " + floatToStr(min) + ", max: " + floatToStr(max));
	}
	return f;
}

const std::string &Properties::getString(const std::string &key) const{
	PropertyMap::const_iterator it;
	it= propertyMap.find(key);
	if(it==propertyMap.end()){
		throw std::runtime_error("Value not found in propertyMap: " + key + ", loaded from: " + path);
	}
	else{
		return it->second;
	}
}

void Properties::setInt(const std::string &key, int value){
	setString(key, intToStr(value));
}

void Properties::setBool(const std::string &key, bool value){
	setString(key, boolToStr(value));
}

void Properties::setFloat(const std::string &key, float value){
	setString(key, floatToStr(value));
}

void Properties::setString(const std::string &key, const std::string &value){
	propertyMap.erase(key);
	propertyMap.insert(PropertyPair(key, value));
}

std::string Properties::toString(){
	std::string rStr;
	
	for(PropertyMap::iterator pi= propertyMap.begin(); pi!=propertyMap.end(); pi++)
		rStr+= pi->first + "=" + pi->second + "\n";

	return rStr;
}

}}//end namepsace
