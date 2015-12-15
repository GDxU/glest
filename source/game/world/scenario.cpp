

#include "scenario.h"

#include <stdexcept>

#include "logger.h"
#include "xml_parser.h"
#include "util.h"
#include "game_util.h"






namespace Glest {

// =====================================================
//	class Scenario
// =====================================================

Scenario::~Scenario(){

}

void Scenario::load(const std::string &path){
	try{
		std::string name= cutLastExt(lastDir(path));
		Logger::getInstance().add("Scenario: "+formatString(name), true);

		//parse xml
		XmlTree xmlTree;
		xmlTree.load(path);
		const XmlNode *scenarioNode= xmlTree.getRootNode();
		const XmlNode *scriptsNode= scenarioNode->getChild("scripts");

		for(int i= 0; i<scriptsNode->getChildCount(); ++i){
			const XmlNode *scriptNode = scriptsNode->getChild(i);

			scripts.push_back(Script(getFunctionName(scriptNode), scriptNode->getText()));
		}
	}
	//std::exception handling (conversions and so on);
    catch (const std::exception &e){
        throw std::runtime_error("Error: " + path + "\n" + e.what());
	}
}

std::string Scenario::getScenarioPath(const std::string &dir, const std::string &scenarioName){
	return dir + "/" + scenarioName + "/" + scenarioName + ".xml";
}

std::string Scenario::getFunctionName(const XmlNode *scriptNode){
	std::string name= scriptNode->getName();

	for(int i= 0; i<scriptNode->getAttributeCount(); ++i){
		name+= "_" + scriptNode->getAttribute(i)->getValue();
	}
	return name;
}

}//end namespace
