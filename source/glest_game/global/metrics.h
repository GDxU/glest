

#ifndef _GLEST_GAME_METRICS_H_
#define _GLEST_GAME_METRICS_H_

#include "config.h"

namespace Glest {

// =====================================================
//	class Metrics
// =====================================================

class Metrics{
private:
	int virtualW;
	int virtualH;
	int screenW;
	int screenH;
	int minimapX;
	int minimapY;
	int minimapW;
	int minimapH;
	int displayX;
	int displayY;
	int displayH;
	int displayW;

private:
	Metrics();

public:
	static const Metrics &getInstance();
	
	int getVirtualW() const	{return virtualW;}
	int getVirtualH() const	{return virtualH;}
	int getScreenW() const	{return screenW;}
	int getScreenH() const	{return screenH;}
	int getMinimapX() const	{return minimapX;}
	int getMinimapY() const	{return minimapY;}
	int getMinimapW() const	{return minimapW;}
	int getMinimapH() const	{return minimapH;}
	int getDisplayX() const	{return displayX;}
	int getDisplayY() const	{return displayY;}
	int getDisplayH() const	{return displayH;}
	int getDisplayW() const	{return displayW;}
	float getAspectRatio() const;
	
	int toVirtualX(int w) const;
	int toVirtualY(int h) const;

	bool isInDisplay(int x, int y) const;
	bool isInMinimap(int x, int y) const;
};

}//end namespace

#endif
