#include "Target.h"
#include "Cylinder.h"
#include "Torus.h"

Target::Target(void)
{
		VisualObject * verticalCrosshair = new Cylinder(0.5f, 0.025f);
		verticalCrosshair->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		verticalCrosshair->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.25f, 0.0f)) * rotate(mat4(1.0f), 90.0f, vec3(1.0f, 0.0f, 0.0f));
		this->addChild(verticalCrosshair);

		VisualObject * horizontalCrosshair = new Cylinder(0.5f, 0.025f);
		horizontalCrosshair->material.setAmbientAndDiffuseMat(vec4(1.0f, 0.0f, 0.0f, 1.0f));
		horizontalCrosshair->fixedTransformation = translate(mat4(1.0f), vec3(-0.25f, 0.0f, 0.0f)) * rotate(mat4(1.0f), 90.0f, vec3(0.0f, 1.0f, 0.0f));
		this->addChild(horizontalCrosshair);

		VisualObject * bullsEye = new Cylinder(0.001, 0.2f); 
		bullsEye->material.setAmbientAndDiffuseMat(vec4(0.5f, 0.5f, 0.5f, 0.2f));
		this->addChild(bullsEye);

}


void Target::setShader(GLuint shaderProgram )
{

	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->setShader(shaderProgram);
	}
}
