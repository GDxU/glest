

#include "util.h"

#include <ctime>
#include <cassert>
#include <stdexcept>
#include <cstring>
#include <cstdio>

#include "Windows.h"
#include <stringapiset.h>





namespace Glest {

std::string lastDir(const std::string &s){
	size_t i= s.find_last_of('/');
	size_t j= s.find_last_of('\\');
	size_t pos;

    if (i == std::string::npos){
		pos= j;
	}
    else if (j == std::string::npos){
		pos= i;
	}
	else{
		pos= i<j? j: i;
	}

    if (pos == std::string::npos){
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

    if (i == std::string::npos){
		pos= j;
	}
    else if (j == std::string::npos){
		pos= i;
	}
	else{
		pos= i<j? j: i;
	}

    if (pos == std::string::npos){
		throw std::runtime_error(std::string(__FILE__)+"cutLastFile - i==string::npos");
	}

	return (s.substr(0, pos));
}

std::string cutLastExt(const std::string &s){
     size_t i= s.find_last_of('.');

     if (i == std::string::npos){
          throw std::runtime_error(std::string(__FILE__)+"cutLastExt - i==string::npos");
	 }

     return (s.substr(0, i));
}

std::string ext(const std::string &s){
     size_t i;
     
     i=s.find_last_of('.')+1;

     if (i == std::string::npos){
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

void copyStringToBuffer(char *buffer, int bufferSize, const std::string& s){
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

bool String2WString(const std::string& in, std::wstring& out)
{
    int nLen = (int)in.length();
    out.resize(nLen);
    
    return 0 != MultiByteToWideChar(CP_ACP, 0, (LPCSTR)in.c_str(), nLen, (LPWSTR)out.c_str(), nLen);
}

bool WString2String(const std::wstring& in, std::string& out)
{
    int nLen = (int)in.length();
    out.resize(nLen);
    return 0 != WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)in.c_str(), nLen, (LPSTR)out.c_str(), nLen, NULL, NULL);
}

}//end namespace
