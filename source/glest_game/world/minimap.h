

#ifndef _GLEST_GAME_MINIMAP_H_
#define _GLEST_GAME_MINIMAP_H_

#include "pixmap.h"
#include "texture.h"
#include "renderer.h"

namespace Glest {







class World;

enum ExplorationState{
    esNotExplored,
    esExplored,
    esVisible
};

// =====================================================
// 	class Minimap  
//
/// State of the in-game minimap
// =====================================================

class Minimap{
private:
	Pixmap2D *fowPixmap0;
	Pixmap2D *fowPixmap1;
	Texture2D *tex;
	Texture2D *fowTex;    //Fog Of War Texture2D
	bool fogOfWar;

private:
	static const float exploredAlpha;

public:
    void init(int x, int y, const World *world);
	Minimap();
	~Minimap();

	const Texture2D *getFowTexture() const	{return fowTex;}
	const Texture2D *getTexture() const		{return tex;}

	void incFowTextureAlphaSurface(const Vec2i &sPos, float alpha);
	void resetFowTex();
	void updateFowTex(float t);

private:
	void computeTexture(const World *world);
};

}//end namespace 

#endif
