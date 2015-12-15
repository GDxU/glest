

#ifndef _SHARED_UTIL_CONVERSION_H_
#define _SHARED_UTIL_CONVERSION_H_

#include <string>




namespace Glest {

bool strToBool(const std::string &s);
int strToInt(const std::string &s);
float strToFloat(const std::string &s); 

bool strToBool(const std::string &s, bool *b);
bool strToInt(const std::string &s, int *i);
bool strToFloat(const std::string &s, float *f);

std::string boolToStr(bool b);
std::string intToStr(int i);
std::string intToHex(int i);
std::string floatToStr(float f);
std::string doubleToStr(double f);

}//end namespace

#endif
