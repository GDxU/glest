

#include "shader_gl.h"

#include <fstream>

#include "opengl.h"




namespace Glest {

// =====================================================
//	class ShaderProgramGl
// =====================================================

ShaderProgramGl::ShaderProgramGl(){
	inited= false;
}

void ShaderProgramGl::init(){
	if(!inited){
		assertGl();
		handle= glCreateProgramObjectARB();
		assertGl();
		inited= true;
	}
}

void ShaderProgramGl::end(){
	if(inited){
		assertGl();
		glDeleteObjectARB(handle);
		assertGl();
		inited= false;
	}
}

void ShaderProgramGl::attach(VertexShader *vertexShader, FragmentShader *fragmentShader){
	this->vertexShader= vertexShader;
	this->fragmentShader= fragmentShader;
}

bool ShaderProgramGl::link(std::string &messages){
	assertGl();

	VertexShaderGl *vertexShaderGl= static_cast<VertexShaderGl*>(vertexShader);
	FragmentShaderGl *fragmentShaderGl= static_cast<FragmentShaderGl*>(fragmentShader);

	const ShaderSource *vss= vertexShaderGl->getSource();
	const ShaderSource *fss= fragmentShaderGl->getSource();
	messages= "Linking program: " + vss->getPathInfo() + ", " + fss->getPathInfo() + "\n";

	//attach
	glAttachObjectARB(handle, vertexShaderGl->getHandle());
	glAttachObjectARB(handle, fragmentShaderGl->getHandle());

	assertGl();

	//bind attributes
	for(int i=0; i<attributes.size(); ++i){
		int a= attributes[i].second;
		std::string s= attributes[i].first;
		glBindAttribLocationARB(handle, attributes[i].second, attributes[i].first.c_str());
	}

	assertGl();

	//link
	glLinkProgramARB(handle);
	glValidateProgramARB(handle);

	assertGl();

	//log
	GLint logLength= 0;
	glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
	char *buffer= new char[logLength+1];
	glGetInfoLogARB(handle, logLength+1, NULL, buffer);
	messages+= buffer;
	delete [] buffer;

	assertGl();

	//status
	GLint status= false;
	glGetObjectParameterivARB(handle, GL_OBJECT_LINK_STATUS_ARB, &status);
	
	assertGl();

	return status!=0;
}

void ShaderProgramGl::activate(){
	assertGl();
	glUseProgramObjectARB(handle);
	assertGl();
}

void ShaderProgramGl::deactivate(){
	assertGl();
	glUseProgramObjectARB(0);
	assertGl();
}

void ShaderProgramGl::setUniform(const std::string &name, int value){
	assertGl();
	glUniform1iARB(getLocation(name), value);
	assertGl();
}

void ShaderProgramGl::setUniform(const std::string &name, float value){
	assertGl();
	glUniform1fARB(getLocation(name), value);
	assertGl();
}

void ShaderProgramGl::setUniform(const std::string &name, const Vec2f &value){
	assertGl();
	glUniform2fvARB(getLocation(name), 1, value.ptr());
	assertGl();
}

void ShaderProgramGl::setUniform(const std::string &name, const Vec3f &value){
	assertGl();
	glUniform3fvARB(getLocation(name), 1, value.ptr());
	assertGl();
}

void ShaderProgramGl::setUniform(const std::string &name, const Vec4f &value){
	assertGl();
	glUniform4fvARB(getLocation(name), 1, value.ptr());
	assertGl();
}

void ShaderProgramGl::setUniform(const std::string &name, const Matrix3f &value){
	assertGl();
	glUniformMatrix3fvARB(getLocation(name), 1, GL_FALSE, value.ptr());
	assertGl();
}

void ShaderProgramGl::setUniform(const std::string &name, const Matrix4f &value){
	assertGl();
	glUniformMatrix4fvARB(getLocation(name), 1, GL_FALSE, value.ptr());
	assertGl();
}

void ShaderProgramGl::bindAttribute(const std::string &name, int index){
	attributes.push_back(AttributePair(name, index));
}

GLint ShaderProgramGl::getLocation(const std::string &name){
	GLint location= glGetUniformLocationARB(handle, name.c_str());
	if(location==-1){
		throw std::runtime_error("Can't locate uniform: "+ name);
	}
	return location;
}

// ===============================================
//	class ShaderGl
// ===============================================

ShaderGl::ShaderGl(){
	inited= false;
}

void ShaderGl::load(const std::string &path){
	source.load(path);
}

bool ShaderGl::compile(std::string &messages){
	
	assertGl();

	messages= "Compiling shader: " + source.getPathInfo() + "\n";

	//load source
	GLint length= source.getCode().size();
	const GLcharARB *csource= source.getCode().c_str();
	glShaderSourceARB(handle, 1, &csource, &length);

	//compile
	glCompileShaderARB(handle);
	
	//log
	GLint logLength= 0;
	glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength);
	char *buffer= new char[logLength+1];
	glGetInfoLogARB(handle, logLength+1, NULL, buffer);
	messages+= buffer;
	delete [] buffer;

	//status
	GLint status= false;
	glGetObjectParameterivARB(handle, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	assertGl();

	return status!=0;
}

void ShaderGl::end(){
	if(inited){
		assertGl();
		glDeleteObjectARB(handle);
		assertGl();
	}
}

// ===============================================
//	class VertexShaderGl
// ===============================================

void VertexShaderGl::init(){
	if(!inited){
		assertGl();
		handle= glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		assertGl();
		inited= true;
	}
}

// ===============================================
//	class FragmentShaderGl
// ===============================================

void FragmentShaderGl::init(){
	if(!inited){
		assertGl();
		handle= glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
		assertGl();
		inited= true;
	}
}

}//end namespace
