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

#ifndef _SHARED_GRAPHICS_MATHUTIL_H_
#define _SHARED_GRAPHICS_MATHUTIL_H_

#include <cmath>

#include "vec.h"

namespace Shared{ namespace Graphics{

const float pi= 3.1415926f;
const float sqrt2= 1.41421356f;
const float zero= 1e-6f;
const float infinity= 1e6f;

#undef M_PI
static const float M_PI = 3.14159265358979323846264338327950288f;
static const float M_HALF_PI = M_PI * 0.5f;
static const int M_MIN_INT = 0x80000000;
static const int M_MAX_INT = 0x7fffffff;
static const unsigned M_MIN_UNSIGNED = 0x00000000;
static const unsigned M_MAX_UNSIGNED = 0xffffffff;

static const float M_EPSILON = 0.000001f;
static const float M_LARGE_EPSILON = 0.00005f;
static const float M_MIN_NEARCLIP = 0.01f;
static const float M_MAX_FOV = 160.0f;
static const float M_LARGE_VALUE = 100000000.0f;
static const float M_INFINITY = (float)HUGE_VAL;
static const float M_DEGTORAD = M_PI / 180.0f;
static const float M_DEGTORAD_2 = M_PI / 360.0f;    // M_DEGTORAD / 2.f
static const float M_RADTODEG = 1.0f / M_DEGTORAD;

/// Check whether two floating point values are equal within accuracy.
inline bool Equals(float lhs, float rhs) { return lhs + M_EPSILON >= rhs && lhs - M_EPSILON <= rhs; }

/// Linear interpolation between two float values.
inline float Lerp(float lhs, float rhs, float t) { return lhs * (1.0f - t) + rhs * t; }

/// Linear interpolation between two double values.
inline double Lerp(double lhs, double rhs, float t) { return lhs * (1.0f - t) + rhs * t; }

/// Return the smaller of two floats.
inline float Min(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }

/// Return the larger of two floats.
inline float Max(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }

/// Return absolute value of a float.
inline float Abs(float value) { return value >= 0.0f ? value : -value; }

/// Return the sign of a float (-1, 0 or 1.)
inline float Sign(float value) { return value > 0.0f ? 1.0f : (value < 0.0f ? -1.0f : 0.0f); }

/// Check whether a floating point value is NaN.
/// Use a workaround for GCC, see https://github.com/urho3d/Urho3D/issues/655
#ifndef __GNUC__
inline bool IsNaN(float value) { return value != value; }
#else

inline bool IsNaN(float value)
{
    unsigned u = *(unsigned*)(&value);
    return (u & 0x7fffffff) > 0x7f800000;
}

#endif

/// Clamp a float to a range.
inline float Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

/// Smoothly damp between values.
inline float SmoothStep(float lhs, float rhs, float t)
{
    t = Clamp((t - lhs) / (rhs - lhs), 0.0f, 1.0f); // Saturate t
    return t * t * (3.0f - 2.0f * t);
}

/// Return sine of an angle in degrees.
inline float Sin(float angle) { return sinf(angle * M_DEGTORAD); }

/// Return cosine of an angle in degrees.
inline float Cos(float angle) { return cosf(angle * M_DEGTORAD); }

/// Return tangent of an angle in degrees.
inline float Tan(float angle) { return tanf(angle * M_DEGTORAD); }

/// Return arc sine in degrees.
inline float Asin(float x) { return M_RADTODEG * asinf(Clamp(x, -1.0f, 1.0f)); }

/// Return arc cosine in degrees.
inline float Acos(float x) { return M_RADTODEG * acosf(Clamp(x, -1.0f, 1.0f)); }

/// Return arc tangent in degrees.
inline float Atan(float x) { return M_RADTODEG * atanf(x); }

/// Return arc tangent of y/x in degrees.
inline float Atan2(float y, float x) { return M_RADTODEG * atan2f(y, x); }

/// Return the smaller of two integers.
inline int Min(int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }

/// Return the larger of two integers.
inline int Max(int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }

/// Return absolute value of an integer
inline int Abs(int value) { return value >= 0 ? value : -value; }

/// Clamp an integer to a range.
inline int Clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

/// Check whether an unsigned integer is a power of two.
inline bool IsPowerOfTwo(unsigned value)
{
    if (!value)
        return true;
    while (!(value & 1))
        value >>= 1;
    return value == 1;
}

/// Round up to next power of two.
inline unsigned NextPowerOfTwo(unsigned value)
{
    unsigned ret = 1;
    while (ret < value && ret < 0x80000000)
        ret <<= 1;
    return ret;
}

// =====================================================
//	class Rect
// =====================================================

// 0 +-+
//   | |
//   +-+ 1

template<typename T>
class Rect2{
public:
	Vec2<T> p[2];
public:
	Rect2(){
	};

	Rect2(const Vec2<T> &p0, const Vec2<T> &p1){
		this->p[0]= p0;
		this->p[1]= p1;
	} 

	Rect2(T p0x, T p0y, T p1x, T p1y){
		p[0].x= p0x;
		p[0].y= p0y;
		p[1].x= p1x;
		p[1].y= p1y;
	} 

	Rect2<T> operator*(T scalar){
		return Rect2<T>(
			p[0]*scalar,
			p[1]*scalar);
	}

	Rect2<T> operator/(T scalar){
		return Rect2<T>(
			p[0]/scalar,
			p[1]/scalar);
	}

	bool isInside(const Vec2<T> &p) const{
		return 
			p.x>=this->p[0].x && 
			p.y>=this->p[0].y && 
			p.x<this->p[1].x && 
			p.y<this->p[1].y;
	}

	void clamp(T minX, T minY,T  maxX, T maxY){
		for(int i=0; i<2; ++i){
			if(p[i].x<minX){
				p[i].x= minX;
			}
			if(p[i].y<minY){
				p[i].y= minY;
			}
			if(p[i].x>maxX){
				p[i].x= maxX;
			}
			if(p[i].y>maxY){
				p[i].y= maxY;
			}
		}
	}
};

typedef Rect2<int> Rect2i;
typedef Rect2<char> Rect2c;
typedef Rect2<float> Rect2f;
typedef Rect2<double> Rect2d;

// =====================================================
//	class Quad
// =====================================================

// 0 +-+ 2
//   | |
// 1 +-+ 3

template<typename T>
class Quad2{
public:
	Vec2<T> p[4];
public:
	Quad2(){
	};

	Quad2(const Vec2<T> &p0, const Vec2<T> &p1, const Vec2<T> &p2, const Vec2<T> &p3){
		this->p[0]= p0;
		this->p[1]= p1;
		this->p[2]= p2;
		this->p[3]= p3;
	} 

	explicit Quad2(const Rect2<T> &rect){
		this->p[0]= rect.p[0];
		this->p[1]= Vec2<T>(rect.p[0].x, rect.p[1].y);
		this->p[2]= rect.p[1];
		this->p[3]= Vec2<T>(rect.p[1].x, rect.p[0].y);
	}

	Quad2<T> operator*(T scalar){
		return Quad2<T>(
			p[0]*scalar,
			p[1]*scalar,
			p[2]*scalar,
			p[3]*scalar);
	}

	Quad2<T> operator/(T scalar){
		return Quad2<T>(
			p[0]/scalar,
			p[1]/scalar,
			p[2]/scalar,
			p[3]/scalar);
	}

	Rect2<T> computeBoundingRect() const{
		return Rect2i(
			Min(p[0].x, p[1].x), 
            Min(p[0].y, p[2].y),
			Max(p[2].x, p[3].x), 
            Max(p[1].y, p[3].y));
	}

	bool isInside(const Vec2<T> &pt) const{
		
		if(!computeBoundingRect().isInside(pt))
			return false;

		bool left[4];

		left[0]= (pt.y - p[0].y)*(p[1].x - p[0].x) - (pt.x - p[0].x)*(p[1].y - p[0].y) < 0;
		left[1]= (pt.y - p[1].y)*(p[3].x - p[1].x) - (pt.x - p[1].x)*(p[3].y - p[1].y) < 0;
		left[2]= (pt.y - p[3].y)*(p[2].x - p[3].x) - (pt.x - p[3].x)*(p[2].y - p[3].y) < 0;
		left[3]= (pt.y - p[2].y)*(p[0].x - p[2].x) - (pt.x - p[2].x)*(p[0].y - p[2].y) < 0;
		
		return left[0] && left[1] && left[2] && left[3];
	}

	void clamp(T minX, T minY, T maxX, T maxY){
		for(int i=0; i<4; ++i){
			if(p[i].x<minX){
				p[i].x= minX;
			}
			if(p[i].y<minY){
				p[i].y= minY;
			}
			if(p[i].x>maxX){
				p[i].x= maxX;
			}
			if(p[i].y>maxY){
				p[i].y= maxY;
			}
		}
	}

	float area(){
		Vec2i v0= p[3]-p[0];
		Vec2i v1= p[1]-p[2];

		return 0.5f * ((v0.x * v1.y) - (v0.y * v1.x));
	}
};

typedef Quad2<int> Quad2i;
typedef Quad2<char> Quad2c;
typedef Quad2<float> Quad2f;
typedef Quad2<double> Quad2d;

// =====================================================
//	Misc
// =====================================================

inline int next2Power(int n){
	int i;
	for (i=1; i<n; i*=2);
	return i;
}

template<typename T>
inline T degToRad(T deg){
	return (deg*2*pi)/360;
}

template<typename T>
inline T radToDeg(T rad){
	return (rad*360)/(2*pi);
}

}}//end namespace

#endif
