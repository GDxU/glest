

#ifndef _GLEST_GAME_SURFACEATLAS_H_
#define _GLEST_GAME_SURFACEATLAS_H_

#include <vector>
#include <set>

#include "texture.h"
#include "vec.h"










namespace Glest {

// =====================================================
//	class SurfaceInfo
// =====================================================

class SurfaceInfo{
private:
	const Pixmap2D *center;
	const Pixmap2D *leftUp;
	const Pixmap2D *rightUp;
	const Pixmap2D *leftDown;
	const Pixmap2D *rightDown;
	Vec2f coord;
	const Texture2D *texture;

public:
	SurfaceInfo(const Pixmap2D *center);
	SurfaceInfo(const Pixmap2D *lu, const Pixmap2D *ru, const Pixmap2D *ld, const Pixmap2D *rd);
	bool operator==(const SurfaceInfo &si) const;

	const Pixmap2D *getCenter() const		{return center;}
	const Pixmap2D *getLeftUp() const		{return leftUp;}
	const Pixmap2D *getRightUp() const		{return rightUp;}
	const Pixmap2D *getLeftDown() const		{return leftDown;}
	const Pixmap2D *getRightDown() const	{return rightDown;}
	const Vec2f &getCoord() const			{return coord;}
	const Texture2D *getTexture() const		{return texture;}

	void setCoord(const Vec2f &coord)			{this->coord= coord;}
	void setTexture(const Texture2D *texture)	{this->texture= texture;}
};	

// =====================================================
// 	class SurfaceAtlas
//
/// Holds all surface textures for a given Tileset
// =====================================================

class SurfaceAtlas{
private:
	typedef std::vector<SurfaceInfo> SurfaceInfos;

private:
	SurfaceInfos surfaceInfos;
	int surfaceSize;

public:
	SurfaceAtlas();

	void addSurface(SurfaceInfo *si);
	float getCoordStep() const;

private:
	void checkDimensions(const Pixmap2D *p);
};

}//end namespace

#endif
