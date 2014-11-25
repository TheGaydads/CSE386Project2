#include "GlutSphere.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

GlutSphere::GlutSphere( glm::vec4 color, GLdouble radius, GLint slices, GLint stacks)
	:GlutObject(color)
{
	this->objectColor = color;
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}


// Preform drawing operations
void GlutSphere::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	//glutSolidGlutCube( dInnerRadius, dOuterRadius, nSides, nRings);

	glutSolidSphere(radius, slices, stacks);

} // end draw

