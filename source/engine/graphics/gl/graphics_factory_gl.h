

#ifndef _SHARED_GRAPHICS_GL_GRAPHICSFACTORYGL_H_
#define _SHARED_GRAPHICS_GL_GRAPHICSFACTORYGL_H_

#include "texture_manager.h"
#include "model_manager.h"
#include "particle.h"
#include "font_manager.h"
#include "graphics_factory.h"
#include "text_renderer_gl.h"
#include "model_renderer_gl.h"
#include "particle_renderer_gl.h"
#include "model_gl.h"
#include "texture_gl.h"
#include "font_gl.h"

namespace Glest {

// =====================================================
//	class GraphicsFactoryGl
// =====================================================

class GraphicsFactoryGl: public GraphicsFactory{
public:

	//textures
	virtual TextureManager *newTextureManager()		{return new TextureManager();}
	virtual Texture1D *newTexture1D()				{return new Texture1DGl();}
	virtual Texture2D *newTexture2D()				{return new Texture2DGl();}
	virtual Texture3D *newTexture3D()				{return new Texture3DGl();}
	virtual TextureCube *newTextureCube()			{return new TextureCubeGl();}
	
	//models
	virtual ModelManager *newModelManager()			{return new ModelManager();}
	virtual ModelRenderer *newModelRenderer()		{return new ModelRendererGl();}
	virtual Model *newModel()						{return new ModelGl();}

	//text
	virtual FontManager *newFontManager()			{return new FontManager();}
	virtual TextRenderer2D *newTextRenderer2D()		{return new TextRenderer2DGl();}
	virtual TextRenderer3D *newTextRenderer3D()		{return new TextRenderer3DGl();}
	virtual Font2D *newFont2D()						{return new Font2DGl();}
	virtual Font3D *newFont3D()						{return new Font3DGl();}

	//particles
	virtual ParticleManager *newParticleManager()	{return new ParticleManager();}
	virtual ParticleRenderer *newParticleRenderer()	{return new ParticleRendererGl();}
};

}//end namespace

#endif
