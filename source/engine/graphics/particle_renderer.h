

#ifndef _SHARED_GRAPHICS_PARTICLERENDERER_H_
#define _SHARED_GRAPHICS_PARTICLERENDERER_H_

#include "particle.h"

namespace Glest {

class ModelRenderer;

// =====================================================
//	class ParticleRenderer
// =====================================================

class ParticleRenderer{
public:
	//particles
	virtual ~ParticleRenderer(){};
	virtual void renderManager(ParticleManager *pm, ModelRenderer *mr)=0;
	virtual void renderSystem(ParticleSystem *ps)=0;
	virtual void renderSystemLine(ParticleSystem *ps)=0;
	virtual void renderSystemLineAlpha(ParticleSystem *ps)=0;
	virtual void renderSingleModel(AttackParticleSystem *ps, ModelRenderer *mr)=0;
};

}//end namespace

#endif
