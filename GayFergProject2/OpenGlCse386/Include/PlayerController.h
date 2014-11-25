#pragma once
#include "controller.h"
class PlayerController :
	public Controller
{
public:
	//friend void specialKeyCB(int key, int x, int y);

	PlayerController();
	glm::vec4 direction;
	void update(float elapsedTimeSeconds);
	void setXPosition(GLfloat xPosition);
protected:
	GLfloat xPosition;
};

static PlayerController* PlayerControllerPointer;
