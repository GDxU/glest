

#include "opengl.h"

#include <stdexcept>

#include "graphics_interface.h"





namespace Glest {

// =====================================================
//	class Globals
// =====================================================

bool isGlExtensionSupported(const char *extensionName){
    const char *s;
	GLint len;
	const GLubyte *extensionStr= glGetString(GL_EXTENSIONS);

	s= reinterpret_cast<const char *>(extensionStr);
	len= strlen(extensionName);

	while ((s = strstr (s, extensionName)) != NULL) {
		s+= len;

		if((*s == ' ') || (*s == '\0')) {
			return true;
		}
	}

	return false;
}

bool isGlVersionSupported(int major, int minor, int release){
	
	const char *strVersion= getGlVersion();

	//major
	const char *majorTok= strVersion;
	int majorSupported= atoi(majorTok);

	if(majorSupported<major){
		return false;
	}
	else if(majorSupported>major){
		return true;
	}

	//minor
	int i=0;
	while(strVersion[i]!='.'){
		++i;
	}
	const char *minorTok= &strVersion[i]+1;
	int minorSupported= atoi(minorTok);

	if(minorSupported<minor){
		return false;
	}
	else if(minorSupported>minor){
		return true;
	}

	//release
	++i;
	while(strVersion[i]!='.'){
		++i;
	}
	const char *releaseTok= &strVersion[i]+1;

	if(atoi(releaseTok)<release){
		return false;
	}

	return true;
}

const char *getGlVersion(){
	return reinterpret_cast<const char *>(glGetString(GL_VERSION));
}

const char *getGlRenderer(){
	return reinterpret_cast<const char *>(glGetString(GL_RENDERER));
}

const char *getGlVendor(){
	return reinterpret_cast<const char *>(glGetString(GL_VENDOR));
}

const char *getGlExtensions(){
	return reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));	
}

const char *getGlPlatformExtensions(){
    return "";// getPlatformExtensions(static_cast<ContextGl*>(c)->getPlatformContextGl());
}

int getGlMaxLights(){
	int i;
	glGetIntegerv(GL_MAX_LIGHTS, &i);
	return i;
}

int getGlMaxTextureSize(){
	int i;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &i);
	return i;	
}

int getGlMaxTextureUnits(){
	int i;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &i);
	return i;	
}

int getGlModelviewMatrixStackDepth(){
	int i;
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &i);
	return i;
}

int getGlProjectionMatrixStackDepth(){
	int i;
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &i);
	return i;	
}

void checkGlExtension(const char *extensionName){
	if(!isGlExtensionSupported(extensionName)){
        throw std::runtime_error("OpenGL extension not supported: " + std::string(extensionName));
	}
}

}// end namespace
