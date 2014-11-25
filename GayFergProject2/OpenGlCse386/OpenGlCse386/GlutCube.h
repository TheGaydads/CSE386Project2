#ifndef ___GlutCube_H___
#define ___GlutCube_H___

#include "GlutObject.h"


class GlutCube : public GlutObject
{
	public:
		GlutCube( glm::vec4 color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f), 
			GLdouble size = 1.0);

		virtual void draw();
		GLdouble getSize();

	protected:
		
		GLdouble size;
};

#endif /* ___GlutCube_H___ */
