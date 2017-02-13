#include "ViewFrustumCulling.h"

Fustrum::Fustrum()
{
}

Fustrum::Fustrum(PlayerController* tempPlayer)
{
	player = tempPlayer;
}

Fustrum::~Fustrum()
{
}

void Fustrum::setUpCamera()
{
	float angleX;

	nearD = player->getNearPlaneDis();
	farD = player->getFarPlaneDis();
	
	float angle = player->getFOV();
	angle *= HALF_ANG2RAD;

	//compute width and height between near and far plane
	tang = tan(angle);
	sphereFactorY = 1 / cos(angle);

	//half thje hrizontal fov 
	angleX = atan(tang*player->getRatio());
	sphereFactorY = 1 / cos(angleX);
}

//called everytime the camera moves 
void Fustrum::updateCamera()
{
	camPos = player->getWorldPoint();

	Z = player->getlookAtPoint() - player->getWorldPoint();
	Z = normalize(Z);

	X = cross(Z, player->getUpPoint());
	X = normalize(X);

	Y = cross(X, Z);
}

positionToFrustrum Fustrum::isInFrustrum(float radius, vec3 objectPos)
{
	float d;
	float az, ax, ay;
	positionToFrustrum result = INSIDE_FRUSTRUM;

	vec3 v = objectPos - camPos;

	//check the z axis 
	az = dot(v, Z);
	if (az > farD + radius || az < nearD - radius)
	{
		return OUTSIDE_FRUSTRUM;
	}
	if (az > farD - radius || az < nearD + radius)
	{
		return INTERSECT_FRUSTRUM;
	}

	//check the y axis
	ay = dot(v, Y);
	d = sphereFactorY * radius;
	az *= tang;
	if (ay > az+d || ay < -az-d)
	{
		return(OUTSIDE_FRUSTRUM);
	}
	if (ay > az-d || ay < -az+d)
	{
		result = INTERSECT_FRUSTRUM;
	}

	//ax = dot(v, X);
	//az *= player->getRatio();
	//d = sphereFactorX * radius;
	//if (ax > az+d || ax < -az-d)
	//{
	//	return(OUTSIDE_FRUSTRUM);
	//}
	//if (ax > az-d || ax < -az+d)
	//{
	//	result = INTERSECT_FRUSTRUM;
	//}
	return result;
}

positionToFrustrum Fustrum::pointInFrustrum(vec3 point)
{
	float pcz, pcx, pcy, aux;

	//get vectro from cam position
	vec3 v = -point + camPos;

	//check if the z lies between the frustrum
	pcz = dot(v, -Z);
	if (pcz > farD || pcz < nearD)
	{
		return OUTSIDE_FRUSTRUM;
	}

	//check if the y lies between the frustrum
	pcy = dot(v, Y);
	aux = pcz * tang;
	if (pcy > aux || pcy < -aux)
	{
		return OUTSIDE_FRUSTRUM;
	}

	//check if the x lies between the frustrum
	pcx = dot(v, X);
	aux = aux * player->getRatio();
	if (pcx > aux || pcx < -aux)
	{
		return OUTSIDE_FRUSTRUM;
	}

	return INSIDE_FRUSTRUM;

}
