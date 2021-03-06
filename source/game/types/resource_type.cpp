

#include "resource_type.h"

#include "util.h" 
#include "element_type.h"
#include "logger.h"
#include "renderer.h"
#include "xml_parser.h"
#include "game_util.h"




namespace Glest {

// =====================================================
// 	class ResourceType
// =====================================================

void ResourceType::load(const std::string &dir, Checksum* checksum){

	std::string path, str;
	Renderer &renderer= Renderer::getInstance();

	try{
		name= lastDir(dir);
		
		Logger::getInstance().add("Resource type: "+ formatString(name), true);
		path= dir+"/"+name+".xml";

		checksum->addFile(path);

		//tree
		XmlTree xmlTree;
		xmlTree.load(path);
		const XmlNode *resourceNode= xmlTree.getRootNode();

		//image
		const XmlNode *imageNode= resourceNode->getChild("image");
		image= renderer.newTexture2D(rsGame);
		image->load(dir+"/"+imageNode->getAttribute("path")->getRestrictedValue());

		//type
		const XmlNode *typeNode= resourceNode->getChild("type");
		resourceClass= strToRc(typeNode->getAttribute("value")->getRestrictedValue());

		switch(resourceClass){
		case rcTech:{
			//model
			const XmlNode *modelNode= typeNode->getChild("model");
			std::string path=dir+"/" + modelNode->getAttribute("path")->getRestrictedValue();
			
			model= renderer.newModel(rsGame);
			model->load(path);
			
			//default resources
			const XmlNode *defaultAmountNode= typeNode->getChild("default-amount"); 
			defResPerPatch= defaultAmountNode->getAttribute("value")->getIntValue();   
			
			//resource number
			const XmlNode *resourceNumberNode= typeNode->getChild("resource-number"); 
			resourceNumber= resourceNumberNode->getAttribute("value")->getIntValue();   
			
			}
			break;

		case rcTileset:{
			//resource number
			const XmlNode *defaultAmountNode= typeNode->getChild("default-amount"); 
			defResPerPatch= defaultAmountNode->getAttribute("value")->getIntValue();  

			//resource number
			const XmlNode *tilesetObjectNode= typeNode->getChild("tileset-object"); 
			tilesetObject= tilesetObjectNode->getAttribute("value")->getIntValue();  

			}
			break;

		case rcConsumable:{
			//interval
			const XmlNode *intervalNode= typeNode->getChild("interval"); 
			interval= intervalNode->getAttribute("value")->getIntValue();  
			}
			break;
		default:
			break;			
		}
	}
    catch (const std::exception &e){
        throw std::runtime_error("Error loading resource type: " + path + "\n" + e.what());
	}
}


// ==================== misc ==================== 

ResourceClass ResourceType::strToRc(const std::string &s){
	if(s=="tech"){
        return rcTech;
	}
	if(s=="tileset"){
        return rcTileset;
	}
	if(s=="static"){
        return rcStatic;
	}
	if(s=="consumable"){
        return rcConsumable;
	}
    throw std::runtime_error("Error converting from std::string ro resourceClass, found: " + s);
}

}//end namespace
