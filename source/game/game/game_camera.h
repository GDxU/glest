

#ifndef _GLEST_GAME_GAMECAMERA_H_
#define _GLEST_GAME_GAMECAMERA_H_

#include "vec.h"
#include "math_util.h"

namespace Glest {






class Config;

// =====================================================
// 	class GameCamera
//
/// A basic camera that holds information about the game view
// =====================================================

class GameCamera{
public:
	static const float startingVAng;
	static const float startingHAng;
	static const float maxHeight;
	static const float minHeight;
	static const float transitionSpeed;
	static const float centerOffsetZ;

public:
	enum State{
		sGame,
		sFree
	};

private:
	Vec3f pos;
	Vec3f lastPos;

    float hAng;	//YZ plane positive -Z axis
    float vAng;	//XZ plane positive +Z axis
	float lastHAng;	
    float lastVAng;	
    
	float rotate;

	Vec3f move;
	Vec3b stopMove;

	float stateTransition;
	State state;

	int limitX;
	int limitY;


	//config
	float speed;
	bool clampBounds;

public:
    GameCamera();

	void init(int limitX, int limitY);

    //get
	float getHAng() const		{return hAng;};
	float getVAng() const		{return vAng;}
	State getState() const		{return state;}
	const Vec3f &getPos() const	{return pos;}

    //set
	void setRotate(int rotate)	{this->rotate= (float)rotate;}
	void setPos(Vec2f pos);

	void setMoveX(float f)		{this->stopMove.x= false; this->move.x= f;}
	void setMoveY(float f)		{this->stopMove.y= false; this->move.y= f;}
	void setMoveZ(float f)		{this->stopMove.z= false; this->move.z= f;}

	void stopMoveX()			{this->stopMove.x= true;}
	void stopMoveY()			{this->stopMove.y= true;}
	void stopMoveZ()			{this->stopMove.z= true;}

    //other
    void update();
    Quad2i computeVisibleQuad() const;
	void switchState();

	void centerXZ(float x, float z);

private:
	void clampPosXYZ(float x1, float x2, float y1, float y2, float z1, float z2);
    void clampPosXZ(float x1, float x2, float z1, float z2);
    void rotateHV(float h, float v);
    void moveForwardH(float dist);
    void moveSideH(float dist);
    void moveUp(float dist);
};

} //end namespace

#endif
