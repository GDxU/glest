

#include "sound_file_loader.h"


#include "sound.h"
#include "stb_vorbis.h"





namespace Glest {

// =====================================================
//	class WavSoundFileLoader
// =====================================================

void WavSoundFileLoader::open(const std::string &path, SoundInfo *soundInfo){
    char chunkId[]={'-', '-', '-', '-', '\0'};
    uint32 size32= 0;
    uint16 size16= 0; 
    int count;
	
    f.open(path.c_str(), std::ios_base::in | std::ios_base::binary);

	if(!f.is_open()){
        throw std::runtime_error("Error opening wav file: " + std::string(path));
	}

    //RIFF chunk - Id
    f.read(chunkId, 4);

	if(strcmp(chunkId, "RIFF")!=0){
		throw std::runtime_error("Not a valid wav file (first four bytes are not RIFF):" + path);
	}

    //RIFF chunk - Size 
    f.read((char*) &size32, 4);

    //RIFF chunk - Data (WAVE string)
    f.read(chunkId, 4);
    
	if(strcmp(chunkId, "WAVE")!=0){
		throw std::runtime_error("Not a valid wav file (wave data don't start by WAVE): " + path);
	}

    // === HEADER ===

    //first sub-chunk (header) - Id
    f.read(chunkId, 4);
    
	if(strcmp(chunkId, "fmt ")!=0){
		throw std::runtime_error("Not a valid wav file (first sub-chunk Id is not fmt): "+ path);
	}

    //first sub-chunk (header) - Size 
    f.read((char*) &size32, 4);

    //first sub-chunk (header) - Data (encoding type) - Ignore
    f.read((char*) &size16, 2);

    //first sub-chunk (header) - Data (nChannels)
    f.read((char*) &size16, 2);
	soundInfo->setChannels(size16);

    //first sub-chunk (header) - Data (nsamplesPerSecond)
    f.read((char*) &size32, 4);
	soundInfo->setsamplesPerSecond(size32);

    //first sub-chunk (header) - Data (nAvgBytesPerSec)  - Ignore
    f.read((char*) &size32, 4);

    //first sub-chunk (header) - Data (blockAlign) - Ignore
    f.read((char*) &size16, 2);

    //first sub-chunk (header) - Data (nsamplesPerSecond)
    f.read((char*) &size16, 2);
	soundInfo->setBitsPerSample(size16);

	if (soundInfo->getBitsPerSample() != 8 && soundInfo->getBitsPerSample()!=16){
		throw std::runtime_error("Bits per sample must be 8 or 16: " + path);
	}
	bytesPerSecond= soundInfo->getBitsPerSample()*8*soundInfo->getSamplesPerSecond()*soundInfo->getChannels();

    count=0;
    do{
        count++;

        // === DATA ===
        //second sub-chunk (samples) - Id
        f.read(chunkId, 4);
		if(strncmp(chunkId, "data", 4)!=0){
			continue;
		}

        //second sub-chunk (samples) - Size
        f.read((char*) &size32, 4);
		dataSize= size32;
		soundInfo->setSize(dataSize);
    }
    while(strncmp(chunkId, "data", 4)!=0 && count<maxDataRetryCount);

	if(f.bad() || count==maxDataRetryCount){
		throw std::runtime_error("Error reading samples: "+ path);
	}

	dataOffset= f.tellg();

}

uint32 WavSoundFileLoader::read(int8 *samples, uint32 size){
	f.read(reinterpret_cast<char*> (samples), size);
	return f.gcount();
}

void WavSoundFileLoader::close(){
    f.close();
}

void WavSoundFileLoader::restart(){
    f.seekg(dataOffset, std::ios_base::beg);
}

// =======================================
//        Ogg Sound File Loader
// =======================================

void OggSoundFileLoader::open(const std::string &path, SoundInfo *soundInfo){
// 	f= fopen(path.c_str(), "rb");
// 	if(f==NULL){
// 		throw std::runtime_error("Can't open ogg file: "+path);
// 	}

// 	vf= new OggVorbis_File();
// 	if (ov_open_callbacks(f, vf, NULL, 0, OV_CALLBACKS_DEFAULT) < 0)
// 		throw std::runtime_error("Vorbis Can't open ogg file: " + path);
// 
// 	vorbis_info *vi= ov_info(vf, -1);
// 
// 	soundInfo->setChannels(vi->channels);
// 	soundInfo->setsamplesPerSecond(vi->rate);
// 	soundInfo->setBitsPerSample(16);
// 	soundInfo->setSize(static_cast<uint32>(ov_pcm_total(vf, -1))*2);
    int error;
    stb_vorbis* vorbis;

    vorbis = stb_vorbis_open_filename(path.c_str(), &error, 0);

    stb_vorbis_info info = stb_vorbis_get_info(vorbis);

    soundInfo->setBitsPerSample(16);
    soundInfo->setsamplesPerSecond(info.sample_rate);
    soundInfo->setChannels(info.channels);

    soundInfo->setSize(info.max_frame_size);

//     stb_vorbis_stream_length_in_seconds(vorbis);
//     stb_vorbis_stream_length_in_samples(vorbis);

    _stereo = info.channels > 1;
    _vorbis = vorbis;

        //(unsigned char*)data_, dataSize_, &error, 0);

    // 	soundInfo->setsamplesPerSecond(vi->rate);
    // 	soundInfo->setBitsPerSample(16);
    // 	soundInfo->setSize(static_cast<uint32>(ov_pcm_total(vf, -1))*2);

}

uint32 OggSoundFileLoader::read(int8 *dest, uint32 numBytes){
// 	int section;
// 	int totalBytesRead= 0;
// 
// 	while(size>0){
// 		int bytesRead= ov_read(vf, reinterpret_cast<char*> (samples), size,
// 							   0, 2, 1, &section);
// 		if(bytesRead==0){
// 			break;
// 		}
// 		size-= bytesRead;
// 		samples+= bytesRead;
// 		totalBytesRead+= bytesRead; 
// 	}
// 	return totalBytesRead;
    stb_vorbis* vorbis = static_cast<stb_vorbis*>(_vorbis);

    unsigned channels = _stereo ? 2 : 1;
    unsigned outSamples = (unsigned)stb_vorbis_get_samples_short_interleaved(vorbis, channels, (short*)dest, numBytes >> 1);
    unsigned outBytes = (outSamples * channels) << 1;

    // Rewind and retry if is looping and produced less output than should have
    if (outBytes < numBytes/* && !stopAtEnd_*/)
    {
        numBytes -= outBytes;
        stb_vorbis_seek_start(vorbis);
        outSamples =
            (unsigned)stb_vorbis_get_samples_short_interleaved(vorbis, channels, (short*)(dest + outBytes), numBytes >> 1);
        outBytes += (outSamples * channels) << 1;
    }

    return outBytes;
}

void OggSoundFileLoader::close(){

    stb_vorbis_close((stb_vorbis*)_vorbis);
// 
// 	if(vf!=NULL){
// 		ov_clear(vf);
// 		delete vf;
// 		vf= 0;
// 	}
}

void OggSoundFileLoader::restart(){
    stb_vorbis_seek_start((stb_vorbis*)_vorbis);
	//ov_raw_seek(vf, 0);
}

// =====================================================
//	class SoundFileLoaderFactory
// =====================================================

SoundFileLoaderFactory::SoundFileLoaderFactory(){
	registerClass<WavSoundFileLoader>("wav");
	registerClass<OggSoundFileLoader>("ogg");
}

SoundFileLoaderFactory *SoundFileLoaderFactory::getInstance(){
	static SoundFileLoaderFactory soundFileLoaderFactory;
	return &soundFileLoaderFactory;
}

}//end namespace
