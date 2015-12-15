

#ifndef _SHARED_UTIL_RANDOM_H_
#define _SHARED_UTIL_RANDOM_H_

namespace Glest {

// =====================================================
//	class Random
// =====================================================

class Random{
private:
	static const int m;
	static const int a;
	static const int b;

private:
	int lastNumber;
	
public:
	Random();
	void init(int seed);

	int rand();
	int randRange(int min, int max);
	float randRange(float min, float max);
};

}//end namespace

#endif
