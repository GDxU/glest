

#ifndef _SHARED_GRAPHICS_INTERPOLATION_H_
#define _SHARED_GRAPHICS_INTERPOLATION_H_

#include "vec.h"
#include "model.h"

namespace Glest {

// =====================================================
//	class InterpolationData
// =====================================================

class InterpolationData{
private:
	const Mesh *mesh;

	Vec3f *vertices;
	Vec3f *normals;

public:
	InterpolationData(const Mesh *mesh);
	~InterpolationData();

	const Vec3f *getVertices() const	{return vertices==NULL? mesh->getVertices(): vertices;}
	const Vec3f *getNormals() const		{return normals==NULL? mesh->getNormals(): normals;}
	
	void update(float t, bool cycle);
	void updateVertices(float t, bool cycle);
	void updateNormals(float t, bool cycle);
};

}//end namespace

#endif
