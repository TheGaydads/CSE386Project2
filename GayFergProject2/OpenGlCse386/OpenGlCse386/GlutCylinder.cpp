#include "GlutCylinder.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

GlutCylinder::GlutCylinder( glm::vec4 color, GLdouble radius, GLdouble height, GLint slices, GLint stacks)
	:GlutObject(color)
{
	this->radius = radius;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
	this->objectColor = color;
}


// Preform drawing operations
void GlutCylinder::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	//glutSolidGlutCylinder( dInnerRadius, dOuterRadius, nSides, nRings);

	glutSolidCylinder(radius, height, slices, stacks);

} // end draw

