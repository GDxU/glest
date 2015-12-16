
#include "intro.h"	

#include "main_menu.h"
#include "util.h"
#include "game_util.h"
#include "config.h"
#include "program.h"
#include "renderer.h"
#include "sound_renderer.h"
#include "core_data.h"
#include "metrics.h"
#include "auto_test.h"
#include "font.h"
#include "vec.h"
#include "texture.h"

#include <iostream>


namespace Glest { 

Intro::Intro(Program *program):
	ProgramState(program)
{
    timer_ = 0;
    alpha_ = 0;

	SoundRenderer &soundRenderer= SoundRenderer::getInstance();
	soundRenderer.playMusic(CoreData::getInstance().getIntroMusic());
}

void Intro::update(float dt){
    timer_ += dt;
        
    if (timer_ <= 1.0f)
        alpha_ = Min(alpha_ + dt, 1.0f);
    else if (timer_ <= 2.0f)
        alpha_ = 1;
    else if (timer_ <= 3.0f)
        alpha_ = Max(0.0f, alpha_ - dt);
    else
		program->setState(new MainMenu(program));

	if(Config::getInstance().getBool("AutoTest"))
		AutoTest::getInstance().updateIntro(program);
}

void Intro::render(){
	
    Renderer &renderer = Renderer::getInstance();

    renderer.reset2d();
	renderer.clearBuffers();

    CoreData &coreData = CoreData::getInstance();
    const Metrics &metrics = Metrics::getInstance();
    int w = metrics.getVirtualW();
    int h = metrics.getVirtualH();

    renderer.renderTextureQuad(w / 2 - 128, h / 2 - 64, 256, 128, coreData.getLogoTexture(), alpha_);
    renderer.renderText(glestVersionString, coreData.getMenuFontNormal(), alpha_, w / 2 + 64, h / 2 - 32);

	renderer.swapBuffers();
}

void Intro::keyDown(char key){
	mouseUpLeft(0, 0);
}

void Intro::mouseUpLeft(int x, int y){
	SoundRenderer &soundRenderer= SoundRenderer::getInstance();
	soundRenderer.stopMusic(CoreData::getInstance().getIntroMusic());
	soundRenderer.playMusic(CoreData::getInstance().getMenuMusic());
	program->setState(new MainMenu(program));
}

}//end namespace
