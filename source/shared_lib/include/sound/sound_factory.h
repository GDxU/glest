

#ifndef _SHARED_SOUND_SOUNDFACTORY_H_
#define _SHARED_SOUND_SOUNDFACTORY_H_

#include "sound_player.h"

namespace Glest {

// =====================================================
//	class SoundFactory
// =====================================================

class SoundFactory{
public:
	virtual ~SoundFactory(){}
	virtual SoundPlayer *newSoundPlayer()	{return NULL;}	
};

}//end namespace

#endif
