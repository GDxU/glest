

#include "camera.h"


namespace Glest {

// =====================================================
//	class Camera
// =====================================================

Camera::Camera(){
	position= Vec3f(0.0f);
}

void Camera::moveLocalX(float amount){
	position= position + orientation.getLocalXAxis()*amount;
}

void Camera::moveLocalY(float amount){
	position= position + orientation.getLocalYAxis()*amount;
}

void Camera::moveLocalZ(float amount){
	position= position + orientation.getLocalZAxis()*amount;
}

void Camera::addYaw(float amount){
	Quaternion q(EulerAngles(0, amount, 0));
	orientation*= q;
}

void Camera::addPitch(float amount){
	Quaternion q(EulerAngles(amount, 0, 0));
	orientation*= q;
}

void Camera::addRoll(float amount){
	Quaternion q(EulerAngles(0, 0, amount));
	orientation*= q;
}

}//end namespace
