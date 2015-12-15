

#ifndef _GLEST_GAME_PARTICLETYPE_H_
#define _GLEST_GAME_PARTICLETYPE_H_

#include <string>

#include "particle.h"
#include "factory.h"
#include "texture.h"
#include "vec.h"
#include "xml_parser.h"




namespace Glest {












// ===========================================================
//	class ParticleSystemType 
//
///	A type of particle system
// ===========================================================

class ParticleSystemType{
protected:
	std::string type;
	Texture2D *texture;
	Model *model;
	std::string primitive;
	Vec3f offset;
	Vec4f color;
	Vec4f colorNoEnergy;
	float size;
	float sizeNoEnergy;
	float speed;
	float gravity;
	int emissionRate;
	int energyMax;
	int energyVar;

public:
	ParticleSystemType();
	void load(const XmlNode *particleSystemNode, const std::string &dir);

protected:
	void setValues(AttackParticleSystem *ats);
};

// ===========================================================
//	class ParticleSystemTypeProjectile
// ===========================================================

class ParticleSystemTypeProjectile: public ParticleSystemType{
private:
	std::string trajectory;
	float trajectorySpeed;
	float trajectoryScale;
	float trajectoryFrequency;

public:
	void load(const std::string &dir, const std::string &path);
	ProjectileParticleSystem *create();
};

// ===========================================================
//	class ParticleSystemTypeSplash
// ===========================================================

class ParticleSystemTypeSplash: public ParticleSystemType{
public:
	void load(const std::string &dir, const std::string &path);
	SplashParticleSystem *create();

private:
	int emissionRateFade;
	float verticalSpreadA;
	float verticalSpreadB;
	float horizontalSpreadA;
	float horizontalSpreadB;
};

}//end namespace

#endif
