

#ifndef _SHARED_GRAPHICS_MODEL_H_
#define _SHARED_GRAPHICS_MODEL_H_

#include <string>
#include <map>

#include "types.h"
#include "pixmap.h"
#include "texture_manager.h"
#include "texture.h"
#include "model_header.h"








namespace Glest {

class Model;
class Mesh;
class ShadowVolumeData;
class InterpolationData;
class TextureManager;

// =====================================================
//	class Mesh
//
//	Part of a 3D model	
// =====================================================

class Mesh{
private:
	//mesh data
	Texture2D *textures[meshTextureCount];
	std::string texturePaths[meshTextureCount];

	//vertex data counts
	uint32 frameCount;
	uint32 vertexCount;
	uint32 indexCount;

	//vertex data
	Vec3f *vertices;
	Vec3f *normals;
	Vec2f *texCoords;
	Vec3f *tangents;
	uint32 *indices;

	//material data
	Vec3f diffuseColor;
	Vec3f specularColor;
	float specularPower;
	float opacity;

	//properties
	bool twoSided;
	bool customColor;
	
	InterpolationData *interpolationData;

public:
	//init & end
	Mesh();
	~Mesh();
	void init();
	void end();

	//maps
	const Texture2D *getTexture(int i) const	{return textures[i];}
	
	//counts
	uint32 getFrameCount() const			{return frameCount;}
	uint32 getVertexCount() const			{return vertexCount;}
	uint32 getIndexCount() const			{return indexCount;}
	uint32 getTriangleCount() const;

	//data
	const Vec3f *getVertices() const 	{return vertices;}
	const Vec3f *getNormals() const 	{return normals;}
	const Vec2f *getTexCoords() const	{return texCoords;}
	const Vec3f *getTangents() const	{return tangents;}
	const uint32 *getIndices() const 	{return indices;}

	//material
	const Vec3f &getDiffuseColor() const	{return diffuseColor;}
	const Vec3f &getSpecularColor() const	{return specularColor;}
	float getSpecularPower() const			{return specularPower;}
	float getOpacity() const				{return opacity;}

	//properties
	bool getTwoSided() const		{return twoSided;}
	bool getCustomTexture() const	{return customColor;}
	
	//external data
	const InterpolationData *getInterpolationData() const	{return interpolationData;}
	
	//interpolation
	void buildInterpolationData();
	void updateInterpolationData(float t, bool cycle) const;
	void updateInterpolationVertices(float t, bool cycle) const;

	//load
	void loadV2(const std::string &dir, FILE *f, TextureManager *textureManager);
	void loadV3(const std::string &dir, FILE *f, TextureManager *textureManager);
	void load(const std::string &dir, FILE *f, TextureManager *textureManager);
	void save(const std::string &dir, FILE *f);

private:
	void computeTangents();
};

// =====================================================
//	class Model
//
//	3D Model, than can be loaded from a g3d file
// =====================================================

class Model{
private:
	TextureManager *textureManager;

private:
	uint8 fileVersion;
	uint32 meshCount;
	Mesh *meshes;

public: 
	//constructor & destructor
	Model();
	virtual ~Model();
	virtual void init()= 0;
	virtual void end()= 0;

	//data
	void updateInterpolationData(float t, bool cycle) const;
	void updateInterpolationVertices(float t, bool cycle) const;
	void buildShadowVolumeData() const;

	//get
	uint8 getFileVersion() const		{return fileVersion;}
	uint32 getMeshCount() const			{return meshCount;}
	const Mesh *getMesh(int i) const	{return &meshes[i];}

	uint32 getTriangleCount() const;
	uint32 getVertexCount() const;
	
	//io
	void load(const std::string &path);
	void save(const std::string &path);
	void loadG3d(const std::string &path);
	void saveS3d(const std::string &path);

	void setTextureManager(TextureManager *textureManager)	{this->textureManager= textureManager;}

private:
	void buildInterpolationData() const;
};

}//end namespace

#endif
