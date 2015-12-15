

#ifndef _SHARED_GRAPHICS_TEXTUREMANAGER_H_
#define _SHARED_GRAPHICS_TEXTUREMANAGER_H_

#include <vector>

#include "texture.h"




namespace Glest {

// =====================================================
//	class TextureManager
// =====================================================

//manages textures, creation on request and deletion on destruction
class TextureManager{
protected:
	typedef std::vector<Texture*> TextureContainer;
	
protected:
	TextureContainer textures;
	
	Texture::Filter textureFilter;
	int maxAnisotropy;

public:
	TextureManager();
	~TextureManager();
	void init();
	void end();

	void setFilter(Texture::Filter textureFilter);
	void setMaxAnisotropy(int maxAnisotropy);

	Texture *getTexture(const std::string &path);
	Texture1D *newTexture1D();
	Texture2D *newTexture2D();
	Texture3D *newTexture3D();
	TextureCube *newTextureCube();
};


}//end namespace

#endif
