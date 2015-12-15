

#ifndef _SHARED_GRAPHICS_FONT_H_
#define _SHARED_GRAPHICS_FONT_H_

#include <string>
#include "context.h"




namespace Glest {
	
// =====================================================
//	class FontMetrics
// =====================================================

class FontMetrics{
private:
	float *widths;
	float height;

public:
	FontMetrics();
	~FontMetrics();

	void setWidth(int i, float width)	{widths[i]= width;}
	void setHeight(float height)		{this->height= height;}

	float getTextWidth(const std::string &str) const;
	float getHeight() const;
};

// =====================================================
//	class Font
// =====================================================

class Font{
public:
	static const int charCount;
	
public:
	enum Width{
		wNormal= 400,
		wBold= 700
	};

protected:
	std::string type;
	int width;
	bool inited;
	FontMetrics metrics;
	
public:
	//constructor & destructor
	Font();
	virtual ~Font(){};
	virtual void init()=0;
	virtual void end()=0;
	
	//get
	std::string getType() const					{return type;}	
	int getWidth() const					{return width;}
	const FontMetrics *getMetrics() const	{return &metrics;}

	//set
	void setType(std::string type)		{this->type= type;}
	void setWidth(int width)		{this->width= width;}
};

// =====================================================
//	class Font2D
// =====================================================

class Font2D: public Font{
protected:
	int size;

public:
	Font2D();
	
	int getSize() const				{return size;}
	void setSize(int size)			{this->size= size;}
};

// =====================================================
//	class Font3D
// =====================================================

class Font3D: public Font{
protected:
	float depth;

public:
	Font3D();
	
	float getDepth() const			{return depth;}
	void setDepth(float depth)		{this->depth= depth;}
};

void createGlFontBitmaps(uint32 &base, const std::string &type, int size, int width, int charCount, FontMetrics &metrics);
void createGlFontOutlines(uint32 &base, const std::string &type, int width, float depth, int charCount, FontMetrics &metrics);
//const char *getPlatformExtensions(const PlatformContextGl *pcgl);
void* getGlProcAddress(const char *procName);
}//end namespace

#endif
