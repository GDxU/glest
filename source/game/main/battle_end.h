

#ifndef _GLEST_GAME_BATTLEEND_H_
#define _GLEST_GAME_BATTLEEND_H_

#include "program.h"
#include "stats.h"

namespace Glest {

// =====================================================
// 	class BattleEnd  
//
///	ProgramState representing the end of the game
// =====================================================

class BattleEnd: public ProgramState{
private:
	Stats stats;

public:
	BattleEnd(Program *program, const Stats *stats);
	~BattleEnd();
	virtual void update();
	virtual void render();
	virtual void keyDown(char key);
	virtual void mouseDownLeft(int x, int y);
};

}//end namespace

#endif
