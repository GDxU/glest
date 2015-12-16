

#ifndef _GLEST_GAME_GAMECONSTANTS_H_
#define _GLEST_GAME_GAMECONSTANTS_H_

namespace Glest {

// =====================================================
//	class GameConstants
// =====================================================

enum ControlType{
    ctClosed,
	ctCpu,
	ctCpuUltra,
	ctNetwork,
	ctHuman
};

class GameConstants{
public:
	static const int maxPlayers= 4;
	static const int serverPort= 61357;
	static const int updateFps= 40;
	static const int networkFramePeriod= 10;
	static const int networkExtraLatency= 200;
};

}//end namespace

#endif
