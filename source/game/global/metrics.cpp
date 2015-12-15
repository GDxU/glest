

#include "metrics.h"	

#include "element_type.h"

namespace Glest {


// =====================================================
// 	class Metrics
// =====================================================

Metrics::Metrics(){
	Config &config= Config::getInstance();
	
	virtualW= 1000;
	virtualH= 750;

	screenW= config.getInt("ScreenWidth");
	screenH= config.getInt("ScreenHeight");
	
	minimapX= 10;
	minimapY= 750-128-30+16;
	minimapW= 128;
	minimapH= 128;

	displayX= 800;
	displayY= 250;
	displayW= 128;
	displayH= 480;	
}

const Metrics &Metrics::getInstance(){
	static const Metrics metrics;
	return metrics;
}

float Metrics::getAspectRatio() const{
	return static_cast<float>(screenW)/screenH;
}

int Metrics::toVirtualX(int w) const{
	return w*virtualW/screenW;
}

int Metrics::toVirtualY(int h) const{
	return h*virtualH/screenH;
}

bool Metrics::isInDisplay(int x, int y) const{
	return 
        x > displayX &&
        y > displayY &&
        x < displayX+displayW &&
        y < displayY+displayH;
}

bool Metrics::isInMinimap(int x, int y) const{
	return 
        x > minimapX &&
        y > minimapY &&
        x < minimapX+minimapW &&
        y < minimapY+minimapH;
}

}// end namespace
