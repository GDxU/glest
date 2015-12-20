

#ifndef _GLEST_GAME_GRAPHCOMPONENT_H_
#define _GLEST_GAME_GRAPHCOMPONENT_H_

#include <string>
#include <vector>
#include <list>

#include "font.h"
#include "vec.h"








namespace Glest {
	class Renderer;
	class Texture2D;
// ===========================================================
// 	class GraphicComponent
//
//	OpenGL renderer GUI components
// ===========================================================

class Widget{
public:
	static const float animSpeed;
	static const float fadeSpeed;

protected:
    int x, y, w, h;
	int id;
    std::string text;
	const Font2D *font; 
	bool enabled;

	static float anim;
	static float fade;

public:
	Widget();
	virtual ~Widget(){}

	void init(int x, int y, int w, int h);

	void setId(int id) { this->id = id; }
	int getId() const { return id; }

	int getX() const				{ return x; }
	int getY() const				{ return y; }
	int getW() const				{ return w; }
	int getH() const				{ return h; }
	const std::string &getText() const	{ return text; }
	const Font2D *getFont() const	{ return font; }
	bool getEnabled() const			{ return enabled; }

	void setX(int x)					{ this->x = x; }
	void setY(int y)					{ this->y = y; }
	void setW(int w)					{ this->w = w; }
	void setH(int h)					{ this->h = h; }
	void setText(const std::string &text)	{ this->text = text; }
	void setFont(const Font2D *font)	{ this->font = font; }
	void setEnabled(bool enabled)		{ this->enabled = enabled; }

	virtual bool mouseMove(int x, int y);
	virtual bool mouseClick(int x, int y);
	virtual void draw(Renderer* render);

	static void update();
	static void resetFade();
	static float getAnim()	{ return anim; }
	static float getFade()	{ return fade; }
};

class GraphicImage : public Widget
{
public:
	virtual void draw(Renderer* render);
	virtual void init(int x, int y, int w, int h);

	void setTexture(Texture2D* tex);

protected:
	Texture2D* _texture;
};

// ===========================================================
// 	class GraphicLabel  
// ===========================================================

class GraphicLabel: public Widget{
public:
	static const int defH;
	static const int defW;

private:
	bool centered;

public:
	void init(int x, int y, int w=defW, int h=defH, bool centered= false);

	bool getCentered() const	{return centered;}

	void setCentered(bool centered)	{this->centered= centered;}
	virtual void draw(Renderer* render);
};

// ===========================================================
// 	class GraphicButton  
// ===========================================================

class GraphicButton: public Widget{
private:
	bool lighted;
		
public:
	void init(int x, int y, int w, int h);

	bool getLighted() const			{return lighted;}
	
	void setLighted(bool lighted)	{this->lighted= lighted;}
	virtual bool mouseMove(int x, int y);  
	virtual void draw(Renderer* render);
};

// ===========================================================
// 	class GraphicListBox  
// ===========================================================

class GraphicListBox: public Widget{
public:
	static const int defH;
	static const int defW;

private:
    GraphicButton graphButton1, graphButton2;
    std::vector<std::string> items;
    int selectedItemIndex;
	
public:       
    void init(int x, int y, int w=defW, int h=defH);
    
	int getItemCount() const				{return items.size();}
	int getSelectedItemIndex() const		{return selectedItemIndex;}
	std::string getSelectedItem() const			{return items[selectedItemIndex];}
	const GraphicButton *getButton1() const	{return &graphButton1;}
	const GraphicButton *getButton2() const	{return &graphButton2;}

    void pushBackItem(const std::string& item);
    void setItems(const std::vector<std::string> &items);
	void setSelectedItemIndex(int index);
	void setSelectedItem(const std::string& item);
    
    virtual bool mouseMove(int x, int y);
    virtual bool mouseClick(int x, int y);
	virtual void draw(Renderer* render);
};


class UI
{
public:

	GraphicButton* addButton(const std::string& text, int x, int y, int w, int h);
	GraphicLabel* addLabel(const std::string& text, int x, int y);
	GraphicImage* addImage(Texture2D* tex, int x, int y, int w = -1, int h = -1);

	GraphicListBox* addListBox(int x, int y, int w, int h);


	virtual Widget* mouseMove(int x, int y);
	virtual Widget* mouseClick(int x, int y);
	void draw();

protected:

	std::list<Widget*> _element;
};


// ===========================================================
// 	class GraphicMessageBox  
// ===========================================================

class GraphicMessageBox: public Widget{
public:
	static const int defH;
	static const int defW;

private:
	GraphicButton button1;
	GraphicButton button2;
	int buttonCount;
	std::string header;

public:
	void init(const std::string &button1Str, const std::string &button2Str);
	void init(const std::string &button1Str);

	int getButtonCount() const				{return buttonCount;}
	const GraphicButton *getButton1() const	{return &button1;}
	const GraphicButton *getButton2() const	{return &button2;}
	std::string getHeader() const				{return header;}
	
	void setHeader(std::string header)			{this->header= header;}

    virtual bool mouseMove(int x, int y);
    virtual bool mouseClick(int x, int y);
    bool mouseClick(int x, int y, int &clickedButton);
};

}//end namespace

#endif
