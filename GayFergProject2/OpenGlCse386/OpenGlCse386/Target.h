#pragma once
#include "visualobject.h"
class Target :
	public VisualObject
{
public:
	Target(void);
	virtual void setShader( GLuint shaderProgram );
};

