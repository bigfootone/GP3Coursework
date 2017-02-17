#ifndef _OUTLINEMATERIAL_H
#define _OUTLINEMATERIAL_H

#include "Shader.h"
#include "Common.h"

class OutlineMaterial : public Shader
{
public:

	OutlineMaterial();
	OutlineMaterial(string tempName);
	~OutlineMaterial();

	void bind();
	void unbind();
};

#endif 