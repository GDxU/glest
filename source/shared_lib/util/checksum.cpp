

#include "checksum.h"

#include <cassert>
#include <stdexcept>

#include "util.h"




namespace Glest {

// =====================================================
//	class Checksum
// =====================================================

Checksum::Checksum(){
	sum= 0;
	r= 55665; 
	c1= 52845; 
	c2= 22719;
}

void Checksum::addByte(int8 value){
	int32 cipher= (value ^ (r >> 8));
	
	r= (cipher + r) * c1 + c2;
	sum+= cipher;
}

void Checksum::addString(const std::string &value){
	for(int i= 0; i<value.size(); ++i){
		addByte(value[i]);
	}
}

void Checksum::addFile(const std::string &path){
	
	FILE* file= fopen(path.c_str(), "rb");

	if(file!=NULL){

		addString(lastFile(path));

		while(!feof(file)){
			int8 byte= 0;

			fread(&byte, 1, 1, file);
			addByte(byte);
		}
	}
	else
	{
		throw std::runtime_error("Can not open file: " + path);
	}
	fclose(file);
}

}//end namespace
