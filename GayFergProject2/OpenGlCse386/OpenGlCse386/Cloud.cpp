#include "Cloud.h"
#include "Sphere.h"


Cloud::Cloud(void)
{
	for (int i = 0; i < 5; i++){
		VisualObject * c1 = new Sphere( 0.1f);
		c1->fixedTransformation = translate(mat4(1.0f), vec3(i*.15, 0.0f, 0.0f));
		c1->material.setAmbientAndDiffuseMat(vec4( 0.9f, 0.9, 0.9f, 1.0f)); 
		this->addChild(c1);
	}
	for (int i = 0; i < 4; i++){
		VisualObject * c1 = new Sphere( 0.1f);
		c1->fixedTransformation = translate(mat4(1.0f), vec3(i*.15+.08, 0.15f, 0.0f));
		c1->material.setAmbientAndDiffuseMat(vec4( 0.9f, 0.9, 0.9f, 1.0f)); 
		this->addChild(c1);
	}
	for (int i = 0; i < 3; i++){
		VisualObject * c1 = new Sphere( 0.1f);
		c1->fixedTransformation = translate(mat4(1.0f), vec3(i*.15+.15, 0.075f, 0.07f));
		c1->material.setAmbientAndDiffuseMat(vec4( 0.9f, 0.9, 0.9f, 1.0f)); 
		this->addChild(c1);
	}
}


void Cloud::setShader( GLuint shaderProgram )
{
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->setShader(shaderProgram);
	}
}
