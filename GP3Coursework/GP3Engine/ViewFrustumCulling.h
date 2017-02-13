#ifndef _VIEWFUSTRUMCULLING_H
#define _VIEWFUSTRUMCULLING_H

#include "Common.h"
#include "PlayerController.h"
#include "Plane.h"
#include "Box.h"

#define HALF_ANG2RAD 3.14/360;

enum positionToFrustrum 
{
	OUTSIDE_FRUSTRUM,
	INTERSECT_FRUSTRUM,
	INSIDE_FRUSTRUM,
};

enum fustrumPlane
{
	TOP_PLANE = 0,
	BOTTOM_PLANE = 1,
	LEFT_PLANE = 2,
	RIGHT_PLANE = 3,
	FAR_PLANE = 4,
	NEAR_PLANE = 5,
};

class Fustrum
{
public:
	Fustrum();
	Fustrum(PlayerController* tempPlayer);
	~Fustrum();
	void setUpCamera();
	void updateCamera();
	positionToFrustrum isInFrustrum(float radius, vec3 objectPos);
	positionToFrustrum pointInFrustrum(vec3 point);
	vec3 getCamPos() { return camPos; }
private:
	PlayerController* player;
	vec3 camPos;
	vec3 X, Y, Z;
	float nearD, farD, width, height, tang;
	float sphereFactorX, sphereFactorY;

	vec3 farClippingCenter, nearClippingCenter;
	vec3 farTopLeftPoint, farTopRightPoint, farBottomLeftPoint, farBottomRightPoint;
	vec3 nearTopLeftPoint, nearTopRightPoint, nearBottomLeftPoint, nearBottomRightPoint;
};

#endif