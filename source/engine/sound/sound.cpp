

#include "sound.h"

#include <fstream>
#include <stdexcept>


namespace Glest {
// =====================================================
//	class SoundInfo
// =====================================================

SoundInfo::SoundInfo(){
	channels= 0;
	samplesPerSecond= 0;
	bitsPerSample= 0;
	size= 0;
}

// =====================================================
//	class Sound
// =====================================================

Sound::Sound(){
	volume= 0.0f;
}

// =====================================================
//	class StaticSound
// =====================================================

StaticSound::StaticSound(){
	samples= NULL;
}

StaticSound::~StaticSound(){
	delete [] samples;
}

void StaticSound::load(const std::string &path){
	std::string ext= path.substr(path.find_last_of('.')+1);

	soundFileLoader= SoundFileLoaderFactory::getInstance()->newInstance(ext);

	soundFileLoader->open(path, &info);
	samples= new int8[info.getSize()];
	soundFileLoader->read(samples, info.getSize());
	soundFileLoader->close();

	delete soundFileLoader;
}

// =====================================================
//	class StrSound
// =====================================================

StrSound::StrSound(){
	soundFileLoader= NULL;
	next= NULL;
}

StrSound::~StrSound(){
	close();
}

void StrSound::open(const std::string &path){
	std::string ext= path.substr(path.find_last_of('.')+1);

	soundFileLoader= SoundFileLoaderFactory::getInstance()->newInstance(ext);
	soundFileLoader->open(path, &info);
}

uint32 StrSound::read(int8 *samples, uint32 size){
	return soundFileLoader->read(samples, size);
}

void StrSound::close(){
	if(soundFileLoader!=NULL){
		soundFileLoader->close();
		delete soundFileLoader;
		soundFileLoader= NULL;
	}
}

void StrSound::restart(){
	soundFileLoader->restart();
}

}//end namespace
