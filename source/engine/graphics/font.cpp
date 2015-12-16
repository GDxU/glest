

#include "font.h"

#include "noimpl.h"
#include "SDL.h"
#include <assert.h>
#include <Windows.h>
#include <wingdi.h>
#include <windef.h>
#include "util.h"

namespace Glest {

// =====================================================
//	class FontMetrics
// =====================================================

FontMetrics::FontMetrics(){
	widths= new float[Font::charCount];
	height= 0;

	for(int i=0; i<Font::charCount; ++i){
		widths[i]= 0;
	}	
}

FontMetrics::~FontMetrics(){
	delete [] widths;
}

float FontMetrics::getTextWidth(const std::string &str) const{
	float width= 0.f;
	for(int i=0; i<str.size(); ++i){
		width+= widths[str[i]];
	}
	return width;
}

float FontMetrics::getHeight() const{
	return height;
}

// ===============================================
//	class Font
// ===============================================

const int Font::charCount= 256;

Font::Font(){
	inited= false;
	type= "Times New Roman";
	width= 400;
}

// ===============================================
//	class Font2D
// ===============================================

Font2D::Font2D(){
	size= 10;
}

// ===============================================
//	class Font3D
// ===============================================

Font3D::Font3D(){
	depth= 10.f;
}


void createGlFontBitmaps(uint32 &base, const std::string &type, int size, int width,
    int charCount, FontMetrics &metrics) {
#ifdef X11_AVAILABLE
    Display* display = glXGetCurrentDisplay();
    if (display == 0) {
        throw std::runtime_error("Couldn't create font: display is 0");
    }
    XFontStruct* fontInfo = XLoadQueryFont(display, type.c_str());
    if (!fontInfo) {
        throw std::runtime_error("Font not found.");
    }

    // we need the height of 'a' which sould ~ be half ascent+descent
    metrics.setHeight(static_cast<float>
        (fontInfo->ascent + fontInfo->descent) / 2);
    for (unsigned int i = 0; i < static_cast<unsigned int> (charCount); ++i) {
        if (i < fontInfo->min_char_or_byte2 ||
            i > fontInfo->max_char_or_byte2) {
            metrics.setWidth(i, static_cast<float>(6));
        }
        else {
            int p = i - fontInfo->min_char_or_byte2;
            metrics.setWidth(i, static_cast<float> (
                fontInfo->per_char[p].rbearing
                - fontInfo->per_char[p].lbearing));
        }
    }

    glXUseXFont(fontInfo->fid, 0, charCount, base);
    XFreeFont(display, fontInfo);
#else
    std::wstring wtype;
    String2WString(type, wtype);

    HFONT font = CreateFontW(
        size, 0, 0, 0, width, 0, FALSE, FALSE, ANSI_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
        DEFAULT_PITCH, wtype.c_str());

    assert(font != NULL);

    HDC dc = wglGetCurrentDC();
    SelectObject(dc, font);
    BOOL err = wglUseFontBitmaps(dc, 0, charCount, base);

    FIXED one;
    one.value = 1;
    one.fract = 0;

    FIXED zero;
    zero.value = 0;
    zero.fract = 0;

    MAT2 mat2;
    mat2.eM11 = one;
    mat2.eM12 = zero;
    mat2.eM21 = zero;
    mat2.eM22 = one;

    //metrics
    GLYPHMETRICS glyphMetrics;
    int errorCode = GetGlyphOutline(dc, 'a', GGO_METRICS, &glyphMetrics, 0, NULL, &mat2);
    if (errorCode != GDI_ERROR){
        metrics.setHeight(static_cast<float>(glyphMetrics.gmBlackBoxY));
    }
    for (int i = 0; i < charCount; ++i){
        int errorCode = GetGlyphOutline(dc, i, GGO_METRICS, &glyphMetrics, 0, NULL, &mat2);
        if (errorCode != GDI_ERROR){
            metrics.setWidth(i, static_cast<float>(glyphMetrics.gmCellIncX));
        }
    }

    DeleteObject(font);

    assert(err);
#endif
}

void createGlFontOutlines(uint32 &base, const std::string &type, int width,
    float depth, int charCount, FontMetrics &metrics) {

    std::wstring wtype;

    String2WString(type, wtype);

    HFONT font = CreateFontW(
        10, 0, 0, 0, width, 0, FALSE, FALSE, ANSI_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
        DEFAULT_PITCH, wtype.c_str());

    assert(font != NULL);

    GLYPHMETRICSFLOAT *glyphMetrics = new GLYPHMETRICSFLOAT[charCount];

    HDC dc = wglGetCurrentDC();
    SelectObject(dc, font);
    BOOL err = wglUseFontOutlines(dc, 0, charCount, base, 1000, depth, WGL_FONT_POLYGONS, glyphMetrics);

    //load metrics
    metrics.setHeight(glyphMetrics['a'].gmfBlackBoxY);
    for (int i = 0; i < charCount; ++i){
        metrics.setWidth(i, glyphMetrics[i].gmfCellIncX);
    }

    DeleteObject(font);
    delete[] glyphMetrics;

    assert(err);
}

// const char *getPlatformExtensions(const PlatformContextGl *pcgl) {
// 	return "";
// }

void *getGlProcAddress(const char *procName) {
    void* proc = SDL_GL_GetProcAddress(procName);
    assert(proc != NULL);
    return proc;
}

}//end namespace
