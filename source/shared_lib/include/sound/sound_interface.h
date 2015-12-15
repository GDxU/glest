

#ifndef _SHARED_SOUND_SOUNDINTERFACE_H_
#define _SHARED_SOUND_SOUNDINTERFACE_H_

#include "sound_factory.h"

namespace Glest {

// =====================================================
//	class SoundInterface
// =====================================================

class SoundInterface{
private:
	SoundFactory *soundFactory;

private:
	SoundInterface(){}
	SoundInterface(SoundInterface &);
	void operator=(SoundInterface &);

public:
	static SoundInterface &getInstance();

	void setFactory(SoundFactory *soundFactory);

	SoundPlayer *newSoundPlayer();
};

}//end namespace

#endif
