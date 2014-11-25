#ifndef ___GlutSphere_H___
#define ___GlutSphere_H___

#include "GlutObject.h"


class GlutSphere : public GlutObject
{
	public:
		GlutSphere( glm::vec4 color = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f), GLdouble radius = 0.5, GLint slices = 10, GLint stacks = 10);

		virtual void draw();

	protected:
		
		GLdouble radius;
		GLint slices;
		GLint stacks;
};

#endif /* ___GlutSphere_H___ */
