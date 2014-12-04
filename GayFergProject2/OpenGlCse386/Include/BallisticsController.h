#pragma once
#include "Controller.h"
using namespace glm;

class BallisticsController : 
	public Controller {
public:
	BallisticsController(vec3 position = vec3(0.0f,0.0f,0.0f));
	~BallisticsController(void);

	//Update method that is called by the Visual Object.
	virtual void update(float elapsedTimeSeconds);

	vec3 velocity;
	vec3 position;
	vec3 gravity;

};