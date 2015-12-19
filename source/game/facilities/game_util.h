

#ifndef _GLEST_GAME_GAMEUTIL_H_
#define _GLEST_GAME_GAMEUTIL_H_

#include <string>
#include <vector>

#include "util.h"





namespace Glest {

extern const std::string mailString;
extern const std::string glestVersionString;
extern const std::string networkVersionString;

std::string getCrashDumpFileName();
std::string getNetworkVersionString();
std::string getTeammateName(int i);
std::string getTeammateRole(int i);

std::string formatString(const std::string &str);

}//end namespace

#endif
