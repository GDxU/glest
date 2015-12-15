

#ifndef _SHARED_UTIL_CHECKSUM_H_
#define _SHARED_UTIL_CHECKSUM_H_

#include <string>

#include "types.h"






namespace Glest {

// =====================================================
//	class Checksum
// =====================================================

class Checksum{
private:
	int32	sum;
	int32	r;
    int32	c1;
    int32	c2;
	
public:
	Checksum();

	int32 getSum() const	{return sum;}

	void addByte(int8 value);
	void addString(const std::string &value);
	void addFile(const std::string &path);
};

}//end namespace

#endif
