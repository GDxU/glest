

#ifndef _SHARED_GRAPHICS_GL_MODELRENDERERGL_H_
#define _SHARED_GRAPHICS_GL_MODELRENDERERGL_H_

#include "model_renderer.h"
#include "model.h"
#include "opengl.h"

namespace Glest {

// =====================================================
//	class ModelRendererGl
// =====================================================

class ModelRendererGl: public ModelRenderer{
private:
	bool rendering;
	bool duplicateTexCoords;
	int secondaryTexCoordUnit;
	GLuint lastTexture;

public:
	ModelRendererGl();
	virtual void begin(bool renderNormals, bool renderTextures, bool renderColors, MeshCallback *meshCallback);
	virtual void end();
	virtual void render(const Model *model);
	virtual void renderNormalsOnly(const Model *model);

	void setDuplicateTexCoords(bool duplicateTexCoords)			{this->duplicateTexCoords= duplicateTexCoords;}
	void setSecondaryTexCoordUnit(int secondaryTexCoordUnit)	{this->secondaryTexCoordUnit= secondaryTexCoordUnit;}

private:
	
	void renderMesh(const Mesh *mesh);
	void renderMeshNormals(const Mesh *mesh);
};

}//end namespace

#endif
