#pragma once
#include "controller.h"
class ElevateController :
	public Controller
{
public:
	friend void specialKeyCB(int key, int x, int y);

	ElevateController(void);
	void update(float elapsedTimeSeconds);
	glm::vec4 direction;
protected:
	float elevationAngle;

	
};

static ElevateController* ep;
