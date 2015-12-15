

#ifndef _SHARED_GRAPHICS_CAMERA_H_
#define _SHARED_GRAPHICS_CAMERA_H_

#include "vec.h"
#include "quaternion.h"

namespace Glest {

// =====================================================
//	class Camera
// =====================================================

class Camera{
private:
	Quaternion orientation;
	Vec3f position;
public:
	Camera();

	Vec3f getPosition() const			{return position;}
	Quaternion getOrientation() const	{return orientation;}

	void setPosition(const Vec3f &position)				{this->position= position;}
	void setOrientation(const Quaternion &orientation)	{this->orientation= orientation;}

	void moveLocalX(float amount);
	void moveLocalY(float amount);
	void moveLocalZ(float amount);

	void addYaw(float amount);
	void addPitch(float amount);
	void addRoll(float amount);
};

}//end namespace

#endif
