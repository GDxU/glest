

#ifndef _SHARED_GRAPHICS_GRAPHICSFACTORY_H_
#define _SHARED_GRAPHICS_GRAPHICSFACTORY_H_

#include <cstdlib>

namespace Glest {

class Context;

class TextureManager;
class Texture1D;
class Texture2D;
class Texture3D;
class TextureCube;
	
class ModelManager;
class ModelRenderer;
class Model;

class FontManager;
class TextRenderer2D;
class TextRenderer3D;
class Font2D;
class Font3D;

class ParticleManager;
class ParticleRenderer;
	
class ShaderManager;
class ShaderProgram;
class VertexShader;
class FragmentShader;

// =====================================================
//	class GraphicsFactory
// =====================================================

class GraphicsFactory{
public:
	virtual ~GraphicsFactory(){}

	//context
	virtual Context *newContext()					{return NULL;}

	//textures
	virtual TextureManager *newTextureManager()		{return NULL;}
	virtual Texture1D *newTexture1D()				{return NULL;}
	virtual Texture2D *newTexture2D()				{return NULL;}
	virtual Texture3D *newTexture3D()				{return NULL;}
	virtual TextureCube *newTextureCube()			{return NULL;}
	
	//models
	virtual ModelManager *newModelManager()			{return NULL;}
	virtual ModelRenderer *newModelRenderer()		{return NULL;}
	virtual Model *newModel()						{return NULL;}

	//text
	virtual FontManager *newFontManager()			{return NULL;}
	virtual TextRenderer2D *newTextRenderer2D()		{return NULL;}
	virtual TextRenderer3D *newTextRenderer3D()		{return NULL;}
	virtual Font2D *newFont2D()						{return NULL;}
	virtual Font3D *newFont3D()						{return NULL;}

	//particles
	virtual ParticleManager *newParticleManager()	{return NULL;}
	virtual ParticleRenderer *newParticleRenderer()	{return NULL;}
	
	//shaders
	virtual ShaderManager *newShaderManager()		{return NULL;}
	virtual ShaderProgram *newShaderProgram()		{return NULL;}
	virtual VertexShader *newVertexShader()			{return NULL;}
	virtual FragmentShader *newFragmentShader()		{return NULL;}
};

}//end namespace

#endif
