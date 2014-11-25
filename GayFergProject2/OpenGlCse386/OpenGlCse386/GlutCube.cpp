#include "GlutCube.h"

#include <vector>
#include <math.h>

#include "vertexStructs.h"

GlutCube::GlutCube( glm::vec4 color, GLdouble size)
	:GlutObject(color)
{
	this->size =  size;
	this->objectColor = color;

}

GLdouble GlutCube::getSize() {
	return size;
}

// Preform drawing operations
void GlutCube::draw()
{
	GlutObject::draw();

	// Rings are divisions of the donut. 
	// 2 rings would theoritically cut the dont in half. 4 in would make quaters
	// sides are cuts which are perpendicular to the hole. 
	// 2 sides would theoritically be like slicing a bagel so you could make a sandwich 
	//glutSolidGlutCube( dInnerRadius, dOuterRadius, nSides, nRings);
	glutSolidCube(size);

} // end draw

