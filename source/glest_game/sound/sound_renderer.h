

#ifndef _GLEST_GAME_SOUNDRENDERER_H_
#define _GLEST_GAME_SOUNDRENDERER_H_

#include "sound.h"
#include "sound_player.h"
#include "window.h"
#include "vec.h"

namespace Glest {






// =====================================================
// 	class SoundRenderer
//
///	Wrapper to acces the shared library sound engine
// =====================================================

class SoundRenderer{
public:
	static const int ambientFade;
	static const float audibleDist;
private:
	SoundPlayer *soundPlayer;

	//volume
	float fxVolume;
	float musicVolume;
	float ambientVolume;

private:
	SoundRenderer();

public:
	//misc
	~SoundRenderer();
	static SoundRenderer &getInstance();
	void init(Window *window);
	void update();
	SoundPlayer *getSoundPlayer() const	{return soundPlayer;}

	//music
	void playMusic(StrSound *strSound);
	void stopMusic(StrSound *strSound);
	
	//fx
	void playFx(StaticSound *staticSound, Vec3f soundPos, Vec3f camPos);
	void playFx(StaticSound *staticSound);

	//ambient
	//void playAmbient(StaticSound *staticSound);
	void playAmbient(StrSound *strSound);
	void stopAmbient(StrSound *strSound);
	
	//misc
	void stopAllSounds();
	void loadConfig();
};

}//end namespace

#endif
