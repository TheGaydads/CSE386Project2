#include "PlayerController.h"
using namespace glm;


PlayerController::PlayerController()
	:xPosition(0.0f), direction(0.0,0.0f,-1.0f,0.0f)
{
	PlayerControllerPointer = this;
	//this->gameSize = gameSize;
	//glutSpecialFunc(specialKeyCB);
}

// Sample update method for demonstration purposes.
void PlayerController::update(float elapsedTimeSeconds)
{
	target->modelMatrix = translate(mat4(1.0f), vec3(xPosition, 0.0f, 0.0f)) * translate(mat4(1.0f), vec3(0.0f, -2.5f, 0.0f));
	
} // end update


void PlayerController::setXPosition(GLfloat xPosition) {
	PlayerControllerPointer->xPosition = xPosition;
		
}
