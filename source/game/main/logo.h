

#ifndef _GLEST_GAME_INTRO_H_
#define _GLEST_GAME_INTRO_H_


#include "program.h"



namespace Glest {
    

class Logo: public ProgramState
{
private:
    float timer_;
    float alpha_;

public:
	Logo(Program *program);
    virtual void update(float);
	virtual void render();
	virtual void keyDown(char key);
	virtual void mouseUpLeft(int x, int y);
};

}//end namespace

#endif
