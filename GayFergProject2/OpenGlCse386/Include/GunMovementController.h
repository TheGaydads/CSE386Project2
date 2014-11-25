#pragma once
#include "controller.h"
class GunMovementController :
	public Controller
{
public:
	//friend void specialKeyCB(int key, int x, int y);

	GunMovementController(float gameSize);
	glm::vec4 direction;
	void setElevateAngle(float elevationAngle);
	void update(float elapsedTimeSeconds);
	void setXPosition(GLfloat xPosition);
	float elevationAngle;
protected:
	GLfloat xPosition;
	float gameSize;

};

static GunMovementController* gunMovementControllerPointer;
