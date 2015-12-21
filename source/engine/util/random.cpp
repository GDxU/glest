#include "random.h"

#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <math.h>


namespace Glest {

// =====================================================
//	class Random
// =====================================================

static bool _inited = false;

Random::Random(){
}

void Random::init(){
    if (!_inited) 
    {
        srand((unsigned int)time(NULL));
        _inited = true;
    }
}

int Random::rand(){
	return ::rand() % INT_MAX;
}

int Random::randRange(int min, int max){
	assert(min<=max);
    double r = (double)(::rand() % RAND_MAX) / (double)RAND_MAX;
    return (int)(r*(max - min + 1) + min);
}

float Random::randRange(float min, float max){
    assert(min <= max);
    double r = (double)(::rand() % RAND_MAX) / (double)RAND_MAX;
    return (float)(r*(max - min) + min);
}

}//end namespace
