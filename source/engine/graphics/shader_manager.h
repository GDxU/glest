

#ifndef _SHARED_GRAPHICS_SHADERMANAGER_H_
#define _SHARED_GRAPHICS_SHADERMANAGER_H_

#include "shader.h"

#include <vector>




namespace Glest {

// =====================================================
//	class ShaderManager
// =====================================================

class ShaderManager{
protected:
	typedef std::vector<ShaderProgram*> ShaderProgramContainer;
	typedef std::vector<Shader*> ShaderContainer;

protected:
	ShaderProgramContainer shaderPrograms;
	ShaderContainer shaders;
	std::string logString;

public:
	ShaderManager(){}
	virtual ~ShaderManager();

	ShaderProgram *newShaderProgram();
	VertexShader *newVertexShader();
	FragmentShader *newFragmentShader();

	void init();
	void end();

	const std::string &getLogString() const	{return logString;}
};

}//end namespace

#endif
