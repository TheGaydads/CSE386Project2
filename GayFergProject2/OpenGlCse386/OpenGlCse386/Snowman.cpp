#include "Snowman.h"

#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"

 
Snowman::Snowman( )
	: VisualObject(  )
{
		VisualObject * bottomBall = new Sphere(0.5f);
		//bottomBall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.0f, -2.0f));
		bottomBall->material.setAmbientAndDiffuseMat(vec4( 1.f, 1.0, 1.0f, 1.0f)); 
		this->addChild( bottomBall );

		VisualObject * midBall = new Sphere(0.35f);
		midBall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.6f, 0.0f));
		midBall->material.setAmbientAndDiffuseMat(vec4( 1.f, 1.0, 1.0f, 1.0f)); 
		this->addChild( midBall );

		VisualObject * topBall = new Sphere(0.2f);
		topBall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 1.05f, 0.0f));
		topBall->material.setAmbientAndDiffuseMat(vec4( 1.0f, 1.0, 1.0f, 1.0f)); 
		this->addChild( topBall );

		VisualObject * leftEye = new Sphere(0.03f);
		leftEye->fixedTransformation = translate(mat4(1.0f), vec3(-0.05f, 1.08f, 0.2f));
		leftEye->material.setAmbientAndDiffuseMat(vec4( 0.0f, 0.0, 0.0f, 1.0f)); 
		this->addChild( leftEye );

		VisualObject * rightEye = new Sphere(0.03f);
		rightEye->fixedTransformation = translate(mat4(1.0f), vec3(0.05f, 1.08f, 0.2f));
		rightEye->material.setAmbientAndDiffuseMat(vec4( 0.0f, 0.0, 0.0f, 1.0f)); 
		this->addChild( rightEye );

		VisualObject * carrotNose = new Cone(0.2f, 0.025f);
		carrotNose->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 1.05f, 0.2f));
		carrotNose->material.setAmbientAndDiffuseMat(vec4( 1.0f, 0.4, 0.0f, 1.0f)); 
		this->addChild( carrotNose );

		VisualObject * midButton = new Sphere(0.05f);
		midButton->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.65f, 0.33f));
		midButton->material.setAmbientAndDiffuseMat(vec4( 0.0f, 0.0f, 0.0f, 1.0f)); 
		this->addChild( midButton );

		VisualObject * topButton = new Sphere(0.05f);
		topButton->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.8f, 0.29f));
		topButton->material.setAmbientAndDiffuseMat(vec4( 0.0f, 0.0f, 0.0f, 1.0f)); 
		this->addChild( topButton );

		VisualObject * bottomButton = new Sphere(0.05f);
		bottomButton->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.33f));
		bottomButton->material.setAmbientAndDiffuseMat(vec4( 0.0f, 0.0f, 0.0f, 1.0f)); 
		this->addChild( bottomButton );

		VisualObject * topHat = new Cylinder(0.17f, 0.12f);
		topHat->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 1.2f, 0.0f)) * rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		topHat->material.setAmbientAndDiffuseMat(vec4( 0.0f, 0.0f, 0.0f, 1.0f)); 
		this->addChild( topHat );

		VisualObject * topHatBrim = new Cylinder(0.025f, 0.23f);
		topHatBrim->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, 1.2f, 0.0f)) * rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		topHatBrim->material.setAmbientAndDiffuseMat(vec4( 0.0f, 0.0f, 0.0f, 1.0f)); 
		this->addChild( topHatBrim );

} // end Snowman constructor

void Snowman::setShader( GLuint shaderProgram ) 
{ 
	for (unsigned int i = 0; i < children.size(); i++) {

		children[i]->setShader(shaderProgram);
	}
}



