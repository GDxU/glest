

#include "texture.h"


namespace Glest {

// =====================================================
//	class Texture
// =====================================================

const int Texture::defaultSize= 256;

Texture::Texture(){
	mipmap= true;
	pixmapInit= true;
	wrapMode= wmRepeat;
	format= fAuto;

	inited= false;
}

// =====================================================
//	class Texture1D
// =====================================================

void Texture1D::load(const std::string &path){
	this->path= path;
	pixmap.load(path);
}

// =====================================================
//	class Texture2D
// =====================================================

void Texture2D::load(const std::string &path){
	this->path= path;
	pixmap.load(path);
}

// =====================================================
//	class Texture3D
// =====================================================

void Texture3D::loadSlice(const std::string &path, int slice){
	this->path= path;
	pixmap.loadSlice(path, slice);
}

// =====================================================
//	class TextureCube
// =====================================================

void TextureCube::loadFace(const std::string &path, int face){
	this->path= path;
	pixmap.loadFace(path, face);
}

}//end namespace
