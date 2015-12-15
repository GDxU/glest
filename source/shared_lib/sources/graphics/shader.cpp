

#include "shader.h"

#include <stdexcept>
#include <fstream>





namespace Glest {

// =====================================================
//	class ShaderSource
// =====================================================

void ShaderSource::load(const std::string &path){
	pathInfo+= path + " ";

	//open file
    std::ifstream ifs(path.c_str());
	if(ifs.fail()){
		throw std::runtime_error("Can't open shader file: " + path);
	}

	//read source
	while(true){
        std::fstream::int_type c = ifs.get();
		if(ifs.eof() || ifs.fail() || ifs.bad()){
			break;
		}
		code+= c;
	}
}

}//end namespace
