#ifndef _NOIMPL_H_
#define _NOIMPL_H_

#include <iostream>
#define NOIMPL std::cerr << __FILE__ << "(" << __LINE__ << ")" << __FUNCTION__ << " not implemented.\n";

#endif

