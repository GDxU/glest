

#ifndef _GLEST_GAME_SOUNDCONTAINER_H_
#define _GLEST_GAME_SOUNDCONTAINER_H_

#include <vector>

#include "sound.h"
#include "random.h"






namespace Glest {

// =====================================================
// 	class SoundContainer
//
/// Holds a list of sounds that are usually played at random
// =====================================================

class SoundContainer{
public:
	typedef std::vector<StaticSound*> Sounds;

private:
	Sounds sounds;
	mutable Random random;
	mutable int lastSound;

public:
	SoundContainer();

	void resize(int size)			{sounds.resize(size);}
	StaticSound *&operator[](int i)	{return sounds[i];}

	const Sounds &getSounds() const	{return sounds;}
	StaticSound *getRandSound() const;
};

}//end namespace

#endif
