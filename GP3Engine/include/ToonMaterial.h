#ifndef _TOONAMTERIAL_H
#define _TOONMATERIAL_H

#include "Shader.h"
#include "Common.h"

class ToonMaterial : public Shader
{
public:
	ToonMaterial();
	~ToonMaterial();

	void bind();
	void unbind();

private:

};


#endif