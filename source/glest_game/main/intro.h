

#ifndef _GLEST_GAME_INTRO_H_
#define _GLEST_GAME_INTRO_H_

#include <vector>

#include "program.h"
#include "font.h"
#include "vec.h"
#include "texture.h"










namespace Glest {

// =====================================================
//	class Text
// =====================================================

class Text{
private:
	std::string text;
	Vec2i pos;
    Vec2i size;
	int time;
	const Font2D *font;
	const Texture2D *texture;

public:
	Text(const std::string &text, const Vec2i &pos, int time, const Font2D *font);
	Text(const Texture2D *texture, const Vec2i &pos, const Vec2i &size, int time);

	const std::string &getText() const		{return text;}
	const Font2D *getFont() const		{return font;}
	const Vec2i &getPos() const			{return pos;}
	const Vec2i &getSize() const		{return size;}
	int getTime() const					{return time;}
	const Texture2D *getTexture() const	{return texture;}
};

// =====================================================
// 	class Intro  
//
///	ProgramState representing the intro
// =====================================================

class Intro: public ProgramState{
private:
	static const int introTime;
	static const int appearTime;
	static const int showTime;
	static const int disapearTime;

private:
	std::vector<Text> texts;
	int timer;

public:
	Intro(Program *program);
	virtual void update();
	virtual void render();
	virtual void keyDown(char key);
	virtual void mouseUpLeft(int x, int y);
};

}//end namespace

#endif
