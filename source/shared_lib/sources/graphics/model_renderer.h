


#ifndef _SHARED_GRAPHICS_MODELRENDERER_H_
#define _SHARED_GRAPHICS_MODELRENDERER_H_

#include "model.h"

namespace Glest {

class Texture;

// =====================================================
//	class MeshCallback
//
/// This gets called before rendering mesh
// =====================================================

class MeshCallback{
public:
	virtual ~MeshCallback(){};
	virtual void execute(const Mesh *mesh)= 0;
};

// =====================================================
//	class ModelRenderer
// =====================================================

class ModelRenderer{
protected:
	bool renderNormals;
	bool renderTextures;
	bool renderColors;
	MeshCallback *meshCallback;

public:
	ModelRenderer()	{meshCallback= NULL;}

	virtual ~ModelRenderer(){};

	virtual void begin(bool renderNormals, bool renderTextures, bool renderColors, MeshCallback *meshCallback= NULL)=0;
	virtual void end()=0;
	virtual void render(const Model *model)=0;
	virtual void renderNormalsOnly(const Model *model)=0;
};

}//end namespace

#endif
