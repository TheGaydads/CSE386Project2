#pragma once
#include "VisualObject.h"
class ColoredThreeTriangleFigure :
	public VisualObject
{
public:
	ColoredThreeTriangleFigure(void);
	~ColoredThreeTriangleFigure(void);
	// Buffer all the data that is associated with the vertex 
	// processor for this object. Creates a Vertex Array Object that
	// holds references to the vertex buffers, the index buffer and 
	// the layout specification. 
	virtual void initialize();

	// Render the object and all of its children
	virtual void draw();
};

