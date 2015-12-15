

#include "sound_interface.h"


namespace Glest {

// =====================================================
//	class SoundInterface
// =====================================================

SoundInterface &SoundInterface::getInstance(){
	static SoundInterface soundInterface;
	return soundInterface;
}

void SoundInterface::setFactory(SoundFactory *soundFactory){
	this->soundFactory= soundFactory;	
}

SoundPlayer *SoundInterface::newSoundPlayer(){
	return soundFactory->newSoundPlayer();
}

}//end namespace
