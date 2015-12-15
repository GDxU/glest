

#ifndef _GLEST_GAME_WATER_EFFECTS_H_
#define _GLEST_GAME_WATER_EFFECTS_H_

#include <vector>

#include "vec.h"






namespace Glest {

class Map;

// =====================================================
//	class WaterSplash
// =====================================================

class WaterSplash{
private:
	Vec2f pos;
	float anim;
	bool enabled;

public:
	WaterSplash(const Vec2f &pos);

	void update(float amount);

	const Vec2f &getPos() const	{return pos;}
	float getAnim() const		{return anim;}
	bool getEnabled() const		{return enabled;}
};

// ===============================
// 	class WaterEffects  
//
/// List of water splashes
// ===============================

class WaterEffects{
public:
	typedef std::vector<WaterSplash> WaterSplashes;

private:
	WaterSplashes waterSplashes;
	float anim;
		
public:
	WaterEffects();

	void update();

	float getAmin() const	{return anim;}

	void addWaterSplash(const Vec2f &pos);
	int getWaterSplashCount() const					{return waterSplashes.size();}
	const WaterSplash *getWaterSplash(int i) const	{return &waterSplashes[i];}
};

}//end namespace

#endif
