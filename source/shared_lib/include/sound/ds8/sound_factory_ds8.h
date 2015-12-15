

#ifndef _SHARED_SOUND_SOUNDFACTORYDS8_H_
#define _SHARED_SOUND_SOUNDFACTORYDS8_H_

#include "sound_factory.h"
#include "sound_player_ds8.h"

namespace Glest {

// =====================================================
//	class SoundFactoryDs8
// =====================================================

class SoundFactoryDs8: public SoundFactory{
public:
	virtual SoundPlayer *newSoundPlayer()	{return new SoundPlayerDs8();}	
};

}//end namespace

#endif
