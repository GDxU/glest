

#include "interpolation.h"

#include <cassert>
#include <algorithm>

#include "model.h"
#include "math_util.h"




namespace Glest {

// =====================================================
//	class InterpolationData
// =====================================================

InterpolationData::InterpolationData(const Mesh *mesh){
	vertices= NULL;
	normals= NULL;
	
	this->mesh= mesh;

	if(mesh->getFrameCount()>1){
		vertices= new Vec3f[mesh->getVertexCount()];
		normals= new Vec3f[mesh->getVertexCount()];
	}
}

InterpolationData::~InterpolationData(){
	delete [] vertices;
	delete [] normals;
}

void InterpolationData::update(float t, bool cycle){
	updateVertices(t, cycle);
	updateNormals(t, cycle);
}

void InterpolationData::updateVertices(float t, bool cycle){
	assert(t>=0.0f && t<=1.0f);
	
	uint32 frameCount= mesh->getFrameCount();
	uint32 vertexCount= mesh->getVertexCount();
	const Vec3f *meshVertices= mesh->getVertices();

	if(frameCount>1){
		//misc vars
		uint32 prevFrame= Min<uint32>(static_cast<uint32>(t*frameCount), frameCount-1);
		uint32 nextFrame= cycle? (prevFrame+1) % frameCount: Min(prevFrame+1, frameCount-1); 
		float localT= t*frameCount - prevFrame; 
		uint32 prevFrameBase= prevFrame*vertexCount;
		uint32 nextFrameBase= nextFrame*vertexCount;

		//assertions
		assert(prevFrame<frameCount);
		assert(nextFrame<frameCount);

		//interpolate vertices
		for(uint32 j=0; j<vertexCount; ++j){
			vertices[j]= meshVertices[prevFrameBase+j].lerp(localT, meshVertices[nextFrameBase+j]);
		}
	}
}

void InterpolationData::updateNormals(float t, bool cycle){
	assert(t>=0.0f && t<=1.0f);
	
	uint32 frameCount= mesh->getFrameCount();
	uint32 vertexCount= mesh->getVertexCount();
	const Vec3f *meshNormals= mesh->getNormals();

	if(frameCount>1){
		//misc vars
		uint32 prevFrame= Min<uint32>(static_cast<uint32>(t*frameCount), frameCount-1);
        uint32 nextFrame = cycle ? (prevFrame + 1) % frameCount : Min(prevFrame + 1, frameCount - 1);
		float localT= t*frameCount - prevFrame; 
		uint32 prevFrameBase= prevFrame*vertexCount;
		uint32 nextFrameBase= nextFrame*vertexCount;

		//assertions
		assert(prevFrame<frameCount);
		assert(nextFrame<frameCount);

		//interpolate vertices
		for(uint32 j=0; j<vertexCount; ++j){
			normals[j]= meshNormals[prevFrameBase+j].lerp(localT, meshNormals[nextFrameBase+j]); 
		}
	}
}

}//end namespace 
