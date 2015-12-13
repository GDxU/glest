#ifndef _SHARED_D3D9_D3D9UTIL_H_
#define _SHARED_D3D9_D3D9UTIL_H_

#include <d3d9.h>

#include <string>
#include <stdexcept>

#define D3DCALL(X) checkResult(X, #X);






namespace Shared{ namespace Graphics{ namespace D3d9{

std::string d3dErrorToStr(HRESULT result);

inline void checkResult(HRESULT result, const std::string &functionCall){
	if(result!=D3D_OK){
		throw std::runtime_error("Direct3D Error\nCode: " + d3dErrorToStr(result) + "\nFunction: " + functionCall);
	}
}

}}}//end namespace

#endif