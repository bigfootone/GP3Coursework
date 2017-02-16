#ifndef _CUBE_H
#define _CUBE_H

#include "Object.h"

class Cube : public Object
{

public:

	Cube(){};
	Cube(string tempName);
	void createBuffer() override;
};
#endif