// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2001-2008 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

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
