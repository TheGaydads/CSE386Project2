#pragma once
#include "visualobject.h"
class Cloud :
	public VisualObject
{
public:
	Cloud(void);
	virtual void setShader( GLuint shaderProgram );
};

