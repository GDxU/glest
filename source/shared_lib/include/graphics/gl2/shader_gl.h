// ==============================================================
//	This file is part of Glest Shared Library (www.glest.org)
//
//	Copyright (C) 2001-2005 Martiño Figueroa
//
//	You can redistribute this code and/or modify it under 
//	the terms of the GNU General Public License as published 
//	by the Free Software Foundation; either version 2 of the 
//	License, or (at your option) any later version
// ==============================================================

#ifndef _SHARED_GRAPHICS_GL_SHADERGL_H_
#define _SHARED_GRAPHICS_GL_SHADERGL_H_

#include <map>
#include <vector>

#include "shader.h"
#include "opengl.h"








namespace Shared{ namespace Graphics{ namespace Gl{

// =====================================================
//	class ShaderProgramGl
// =====================================================

class ShaderProgramGl: public ShaderProgram{
private:
	typedef pair<string, int> AttributePair;
	typedef std::vector<AttributePair> Attributes;

private:
	Attributes attributes;
	GLhandleARB handle;
	VertexShader *vertexShader;
	FragmentShader *fragmentShader;
	bool inited;

public:
	ShaderProgramGl();

	GLhandleARB getHandle() const	{return handle;}

	virtual void init();
	virtual void end();

	virtual void attach(VertexShader *vertexShader, FragmentShader *fragmentShader);
	virtual bool link(std::string &messages);
	virtual void activate();

	virtual void setUniform(const std::string &name, int value);
	virtual void setUniform(const std::string &name, float value);
	virtual void setUniform(const std::string &name, const Vec2f &value);
	virtual void setUniform(const std::string &name, const Vec3f &value);
	virtual void setUniform(const std::string &name, const Vec4f &value);
	virtual void setUniform(const std::string &name, const Matrix3f &value);
	virtual void setUniform(const std::string &name, const Matrix4f &value);

	void bindAttribute(const std::string &name, int index);

private:
	GLint getLocation(const std::string &name);
};

// =====================================================
//	class ShaderGl
// =====================================================

class ShaderGl: virtual public Shader{
protected:
	GLhandleARB handle;
	ShaderSource source;
	bool inited;

public:
	ShaderGl();
		
	const ShaderSource *getSource() const	{return &source;}
	GLhandleARB getHandle() const			{return handle;}

	virtual void load(const std::string &path);
	virtual bool compile(std::string &messages);
	virtual void end();
};

// =====================================================
//	class VertexShaderGl
// =====================================================

class VertexShaderGl: public VertexShader, public ShaderGl{
public:
	virtual void init();
};

// =====================================================
//	class FragmentShaderGl
// =====================================================

class FragmentShaderGl: public FragmentShader, public ShaderGl{
public:
	virtual void init();
};

}}}//end namespace

#endif
