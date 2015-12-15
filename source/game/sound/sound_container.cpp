

#include "sound_container.h"

#include "util.h"



namespace Glest {

// =====================================================
// 	class SoundContainer
// =====================================================

SoundContainer::SoundContainer(){
	lastSound= -1;
}

StaticSound *SoundContainer::getRandSound() const{
	switch(sounds.size()){
	case 0:
		return NULL;
	case 1:
		return sounds[0];
	default:
		int soundIndex= random.randRange(0, sounds.size()-1);
		if(soundIndex==lastSound){
			soundIndex= (lastSound+1) % sounds.size();
		}
		lastSound= soundIndex;
		return sounds[soundIndex];
	}
}

}//end namespace
