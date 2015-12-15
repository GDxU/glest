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

#ifndef _SHARED_GRAPHICS_SHADER_H_
#define _SHARED_GRAPHICS_SHADER_H_

#include "vec.h"
#include "matrix.h"
#include "texture.h"

namespace Glest {

// =====================================================
//	class ShaderProgram
// =====================================================

class VertexShader;
class FragmentShader;

class ShaderProgram{
public:
	virtual ~ShaderProgram(){}
	virtual void init()= 0;
	virtual void end()= 0;

	virtual void attach(VertexShader *vs, FragmentShader *fs)= 0;
	virtual bool link(std::string &messages)= 0;
	virtual void activate()= 0;
	virtual void deactivate()= 0;

	virtual void setUniform(const std::string &name, int value)= 0;
	virtual void setUniform(const std::string &name, float value)= 0;
	virtual void setUniform(const std::string &name, const Vec2f &value)= 0;
	virtual void setUniform(const std::string &name, const Vec3f &value)= 0;
	virtual void setUniform(const std::string &name, const Vec4f &value)= 0;
	virtual void setUniform(const std::string &name, const Matrix3f &value)= 0;
	virtual void setUniform(const std::string &name, const Matrix4f &value)= 0;
};

// =====================================================
//	class Shader
// =====================================================

class Shader{
public:
	virtual ~Shader(){}
	virtual void init()= 0;
	virtual void end()= 0;

	virtual void load(const std::string &path)= 0;
	virtual bool compile(std::string &messages)= 0;
};

class VertexShader: virtual public Shader{
};

class FragmentShader: virtual public Shader{
};

// =====================================================
//	class ShaderSource
// =====================================================

class ShaderSource{
private:
	std::string pathInfo;
	std::string code;

public:
	const std::string &getPathInfo() const	{return pathInfo;}
	const std::string &getCode() const		{return code;}

	void load(const std::string &path);
};

}//end namespace

#endif
