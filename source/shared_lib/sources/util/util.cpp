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

#include "util.h"

#include <ctime>
#include <cassert>
#include <stdexcept>
#include <cstring>
#include <cstdio>

#include "leak_dumper.h"

using namespace std;

namespace Shared{ namespace Util{

std::string lastDir(const std::string &s){
	size_t i= s.find_last_of('/');
	size_t j= s.find_last_of('\\');
	size_t pos;

	if(i==string::npos){
		pos= j;
	}
	else if(j==string::npos){
		pos= i;
	}
	else{
		pos= i<j? j: i;
	}

	if (pos==string::npos){ 
		throw std::runtime_error(std::string(__FILE__)+" lastDir - i==string::npos");
	}

	return (s.substr(pos+1, s.length()));
}

std::string lastFile(const std::string &s){
	return lastDir(s);
}

std::string cutLastFile(const std::string &s){
	size_t i= s.find_last_of('/');
	size_t j= s.find_last_of('\\');
	size_t pos;

	if(i==string::npos){
		pos= j;
	}
	else if(j==string::npos){
		pos= i;
	}
	else{
		pos= i<j? j: i;
	}

	if (pos==string::npos){
		throw std::runtime_error(std::string(__FILE__)+"cutLastFile - i==string::npos");
	}

	return (s.substr(0, pos));
}

std::string cutLastExt(const std::string &s){
     size_t i= s.find_last_of('.');

	 if (i==string::npos){
          throw std::runtime_error(std::string(__FILE__)+"cutLastExt - i==string::npos");
	 }

     return (s.substr(0, i));
}

std::string ext(const std::string &s){
     size_t i;
     
     i=s.find_last_of('.')+1;

	 if (i==string::npos){
          throw std::runtime_error(std::string(__FILE__)+"cutLastExt - i==string::npos");
	 }

     return (s.substr(i, s.size()-i));
}

std::string replaceBy(const std::string &s, char c1, char c2){
	std::string rs= s;
	
	for(size_t i=0; i<s.size(); ++i){
		if (rs[i]==c1){
			rs[i]=c2;
		}
	}

	return rs;
}

std::string toLower(const std::string &s){
	std::string rs= s;
	
	for(size_t i=0; i<s.size(); ++i){
		rs[i]= tolower(s[i]);
	}

	return rs;
}

void copyStringToBuffer(char *buffer, int bufferSize, const string& s){
	strncpy(buffer, s.c_str(), bufferSize-1);
	buffer[bufferSize-1]= '\0';
}

// ==================== numeric fcs ====================

float saturate(float value){
	if (value<0.f){
        return 0.f;
	}
	if (value>1.f){
        return 1.f;
	}
    return value;
}

int clamp(int value, int min, int max){
	if (value<min){
        return min;
	}
	if (value>max){
        return max;
	}
    return value;
}

float clamp(float value, float min, float max){
	if (value<min){
        return min;
	}
	if (value>max){
        return max;
	}
    return value;
}

int round(float f){
     return (int) f;
}

// ==================== misc ====================

bool fileExists(const std::string &path){
	FILE* file= fopen(path.c_str(), "rb");
	if(file!=NULL){
		fclose(file);
		return true;
	}
	return false;
}

}}//end namespace
