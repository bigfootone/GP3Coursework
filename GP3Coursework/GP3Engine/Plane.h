#ifndef _PLANE_H
#define _PLANE_H

#include "Common.h"

struct Plane
{
	vec3 normal, point;
	float d;

	void setPlane(vec3 P1, vec3 P2, vec3 P3)
	{
		vec3 vector1 = P1 - P2;
		vec3 vector2 = P3 - P2;
		
		vec3 normal = vector2 * vector1;

		normal = normalize(normal);
		point = P2;

		d = -(normal.x * point.x + normal.y * point.y + normal.z * point.z);
	}

	float distanceFromVec(vec3 tempPoint)
	{
		return (d + (normal.x * tempPoint.x + normal.y * tempPoint.y + normal.z * tempPoint.z));
	}
	
};

#endif