

#include "UIElements.h"

#include <cassert>
#include <algorithm>

#include "metrics.h"
#include "core_data.h"
#include "platform_util.h"
#include "renderer.h"





namespace Glest {

// =====================================================
//	class GraphicComponent
// =====================================================

float Widget::anim= 0.f;
float Widget::fade= 0.f;
const float Widget::animSpeed= 0.02f;
const float Widget::fadeSpeed= 0.01f;

Widget::Widget(){
	enabled= true;
}

void Widget::init(int x, int y, int w, int h){
    this->x= x;
    this->y= y;
    this->w= w;
    this->h= h;
    font= CoreData::getInstance().getMenuFontNormal();
	enabled= true;
}

bool Widget::mouseMove(int x, int y){
    return 
        x > this->x &&
        y > this->y &&
        x < this->x + w &&
        y < this->y + h;
}

bool Widget::mouseClick(int x, int y){
    return mouseMove(x, y);
}

void Widget::draw(Renderer* render)
{

}

void Widget::update(){
	fade+= fadeSpeed;
	anim+= animSpeed;
	if(fade>1.f) fade= 1.f;
	if(anim>1.f) anim= 0.f;
}

void Widget::resetFade(){
	fade= 0.f;
}

// =====================================================
//	class GraphicLabel
// =====================================================

const int GraphicLabel::defH= 20;
const int GraphicLabel::defW= 70;

void GraphicLabel::init(int x, int y, int w, int h, bool centered){
	Widget::init(x, y, w, h);
	this->centered= centered;
}

void GraphicLabel::draw(Renderer* render)
{
	render->renderLabel(this);
}

// =====================================================
//	class GraphicButton
// =====================================================


void GraphicButton::init(int x, int y, int w, int h){
	Widget::init(x, y, w, h);
    lighted= false;
}

bool GraphicButton::mouseMove(int x, int y){
    bool b= Widget::mouseMove(x, y);
    lighted= b;
    return b;
}

void GraphicButton::draw(Renderer* render)
{
	render->renderButton(this);
}

// =====================================================
//	class GraphicListBox
// =====================================================

const int GraphicListBox::defH= 22;
const int GraphicListBox::defW= 140;

void GraphicListBox::init(int x, int y, int w, int h){
	Widget::init(x, y, w, h);

	graphButton1.init(x, y, 22, h);
    graphButton2.init(x+w-22, y, 22, h);
    graphButton1.setText("<");
    graphButton2.setText(">");
    selectedItemIndex=-1;
}       

//queryes
void GraphicListBox::pushBackItem(std::string item){
    items.push_back(item);
    setSelectedItemIndex(0);
}

void GraphicListBox::setItems(const std::vector<std::string> &items){
    this->items= items; 
    setSelectedItemIndex(0);
}

void GraphicListBox::setSelectedItemIndex(int index){
    assert(index>=0 && index<items.size());
    selectedItemIndex= index;
    setText(getSelectedItem());
}

void GraphicListBox::setSelectedItem(std::string item){
    std::vector<std::string>::iterator iter;

    iter= find(items.begin(), items.end(), item);

	if(iter==items.end()){
        throw std::runtime_error("Value not found on list box: " + item);
	}

    setSelectedItemIndex(iter-items.begin());

}
    
bool GraphicListBox::mouseMove(int x, int y){
    return 
        graphButton1.mouseMove(x, y) || 
        graphButton2.mouseMove(x, y);
}

bool GraphicListBox::mouseClick(int x, int y){
	if(!items.empty()){
		bool b1= graphButton1.mouseClick(x, y);
		bool b2= graphButton2.mouseClick(x, y);

		if(b1){
			selectedItemIndex--;
			if(selectedItemIndex<0){
				selectedItemIndex=items.size()-1;
			}
		}
		else if(b2){
			selectedItemIndex++;
			if(selectedItemIndex>=items.size()){
				selectedItemIndex=0;
			}
		}
		setText(getSelectedItem());

		return b1 || b2;
	}
	return false;
}

void GraphicListBox::draw(Renderer* render)
{
	render->renderListBox(this);
}

// =====================================================
//	class GraphicMessageBox
// =====================================================

const int GraphicMessageBox::defH= 240;
const int GraphicMessageBox::defW= 350;
const int GraphicButton_defH = 22;
const int GraphicButton_defW = 90;

void GraphicMessageBox::init(const std::string &button1Str, const std::string &button2Str){
	init(button1Str);

	button1.init(x + (w - GraphicButton_defW) / 4, y + 25, GraphicButton_defW, GraphicButton_defH);
	button1.setText(button1Str);
	button2.init(x + 3 * (w - GraphicButton_defW) / 4, y + 25, GraphicButton_defW, GraphicButton_defH);
	button2.setText(button2Str);
	buttonCount= 2;
}

void GraphicMessageBox::init(const std::string &button1Str){
	font= CoreData::getInstance().getMenuFontNormal();

	h= defH;
	w= defW;
	
	const Metrics &metrics= Metrics::getInstance();

	x= (metrics.getVirtualW()-w)/2;
	y= (metrics.getVirtualH()-h)/2;

	button1.init(x + (w - GraphicButton_defW) / 2, y + 25, GraphicButton_defW, GraphicButton_defH);
	button1.setText(button1Str);
	buttonCount= 1;
}

bool GraphicMessageBox::mouseMove(int x, int y){
	return button1.mouseMove(x, y) || button2.mouseMove(x, y);
}

bool GraphicMessageBox::mouseClick(int x, int y){
    bool b1= button1.mouseClick(x, y);
	bool b2= button2.mouseClick(x, y);
	if(buttonCount==1){
		return b1;
	}
	else{
		return b1 ||b2;
	}
}

bool GraphicMessageBox::mouseClick(int x, int y, int &clickedButton){
    bool b1= button1.mouseClick(x, y);
	bool b2= button2.mouseClick(x, y);

	if(buttonCount==1){
		clickedButton= 1;
		return b1;
	}
	else{
		if(b1){
			clickedButton= 1;
			return true;
		}
		else if(b2){
			clickedButton= 2;
			return true;
		}
	}
	return false;
}

GraphicButton* UI::addButton(const std::string& text, int x, int y, int w /*= -1*/, int h /*= -1*/)
{
	GraphicButton* btn = new GraphicButton;

	btn->init(x, y, w, h);
	btn->setText(text);

	_element.push_back(btn);

	return btn;
}

GraphicLabel* UI::addLabel(const std::string& text, int x, int y)
{
	GraphicLabel* btn = new GraphicLabel;

	btn->init(x, y);
	btn->setText(text);

	_element.push_back(btn);
	return btn;
}

GraphicImage* UI::addImage(Texture2D* tex, int x, int y, int w /*= -1*/, int h /*= -1*/)
{
	GraphicImage* btn = new GraphicImage;

	w = (w != -1) ? w : tex->getPixmap()->getW();
	h = (h != -1) ? h : tex->getPixmap()->getH();
	btn->init(x, y, w, h);
	btn->setTexture(tex);

	_element.push_back(btn);

	return btn;
}

void UI::draw()
{
	Renderer& render = Renderer::getInstance();
	for (std::list<Widget*>::iterator iter = _element.begin(); iter != _element.end(); iter++)
	{
		(*iter)->draw(&render);
	}
}

Widget* UI::mouseMove(int x, int y)
{
	for (std::list<Widget*>::iterator iter = _element.begin(); iter != _element.end(); iter++)
	{
		if ((*iter)->mouseMove(x, y))
			return *iter;
	}
	return NULL;
}

Widget* UI::mouseClick(int x, int y)
{
	for (std::list<Widget*>::iterator iter = _element.begin(); iter != _element.end(); iter++)
	{
		if ((*iter)->mouseClick(x, y))
			return *iter;
	}
	return NULL;
}


void GraphicImage::draw(Renderer* render)
{
	render->renderTextureQuad(x, y, w, h, _texture, getFade());
}

void GraphicImage::init(int x, int y, int w, int h)
{
	Widget::init(x, y, w, h);
}

void GraphicImage::setTexture(Texture2D* tex)
{
	_texture = tex;
}

}//end namespace
