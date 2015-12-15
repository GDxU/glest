

#ifndef _GLEST_GAME_LANG_H_
#define _GLEST_GAME_LANG_H_

#include "properties.h"

namespace Glest {



// =====================================================
// 	class Lang
//
//	std::string table
// =====================================================

class Lang{
private:
	std::string language;
	Properties strings;
	Properties scenarioStrings;

private:
	Lang(){};

public:
	static Lang &getInstance();    
	void loadStrings(const std::string &language);
	void loadScenarioStrings(const std::string &scenarioDir, const std::string &scenarioName);
	std::string get(const std::string &s);
	std::string getScenarioString(const std::string &s);
};

}//end namespace

#endif
