#ifndef ___SNOWMAN_H___
#define ___SNOWMAN_H___

#include "visualobject.h"

class Snowman : public VisualObject
{
	public:
		Snowman( );

		virtual void setShader( GLuint shaderProgram );

};

#endif // ___SNOWMAN_H___
 