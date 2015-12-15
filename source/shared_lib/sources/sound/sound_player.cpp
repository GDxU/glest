

#include "sound_player.h"


namespace Glest {

// =====================================================
//	class SoundPlayerParams
// =====================================================

SoundPlayerParams::SoundPlayerParams(){
	staticBufferCount= 8;
	strBufferCount= 4;
	strBufferSize= 44050*2*2*2;	//2 second buffer
}

}//end namespace
