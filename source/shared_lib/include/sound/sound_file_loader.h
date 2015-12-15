

#ifndef _SHARED_SOUND_SOUNDFILELOADER_H_
#define _SHARED_SOUND_SOUNDFILELOADER_H_

#include <string>
#include <fstream>

#include "types.h"
#include "factory.h"

//struct OggVorbis_File;






namespace Glest {



class SoundInfo;

// =====================================================
//	class SoundFileLoader  
//
///	Interface that all SoundFileLoaders will implement
// =====================================================

class SoundFileLoader{
public:
	virtual ~SoundFileLoader(){}

	virtual void open(const std::string &path, SoundInfo *soundInfo)= 0;
	virtual uint32 read(int8 *samples, uint32 size)= 0;
	virtual void close()= 0;
	virtual void restart()= 0;
};

// =====================================================
//	class WavSoundFileLoader  
//
///	Wave file loader
// =====================================================

class WavSoundFileLoader: public SoundFileLoader{
private:
	static const int maxDataRetryCount= 10;

private:
	uint32 dataOffset;
	uint32 dataSize;
	uint32 bytesPerSecond;
    std::ifstream f;

public:
	virtual void open(const std::string &path, SoundInfo *soundInfo);
	virtual uint32 read(int8 *samples, uint32 size);
	virtual void close();
	virtual void restart();
};

// =====================================================
//	class OggSoundFileLoader 
//
///	OGG sound file loader, uses ogg-vorbis library
// =====================================================

class OggSoundFileLoader: public SoundFileLoader{
private:
    void *_vorbis;
    bool _stereo;
	FILE *f;

public:
	virtual void open(const std::string &path, SoundInfo *soundInfo);
	virtual uint32 read(int8 *samples, uint32 size);
	virtual void close();
	virtual void restart();
};

// =====================================================
//	class SoundFileLoaderFactory
// =====================================================

class SoundFileLoaderFactory: public MultiFactory<SoundFileLoader>{
private:
	SoundFileLoaderFactory();
public:
	static SoundFileLoaderFactory * getInstance();
};

}//end namespace

#endif
