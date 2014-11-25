#ifndef ___GlutCylinder_H___
#define ___GlutCylinder_H___

#include "GlutObject.h"


class GlutCylinder : public GlutObject
{
public:
	GlutCylinder( glm::vec4 color = glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f), GLdouble radius = 1.0, GLdouble height = 1.0 , GLint slices = 10, GLint stacks = 5);
	virtual void draw();

protected:

	GLdouble radius;
	GLdouble height;
	GLint slices;
	GLint stacks;
};

#endif /* ___GlutCylinder_H___ */
