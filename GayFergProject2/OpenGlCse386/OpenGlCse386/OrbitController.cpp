#include "OrbitController.h"

OrbitController::OrbitController(glm::vec3 globalAx, GLfloat globalR, glm::vec3 pos, glm::vec3 ax, GLfloat r)
{
	globalAxis = globalAx;
	globalRate = globalR;
	position = pos;
	axis = ax;
	rate = r;
}
void OrbitController::update(float elapsedTimeSeconds)
{
	//change this
	static float globalRotation = 0.0f;
	globalRotation += elapsedTimeSeconds * globalRate;
	static float rotation = 0.0f;
	rotation += elapsedTimeSeconds * rate;

	glm::mat4 globalRotate = glm::rotate(glm::mat4(1.0f),
			-fmod(rotation, 360.0f), globalAxis);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 objectRotate = glm::rotate(glm::mat4(1.0f), 
			fmod(rotation, 360.0f)*4, axis);

	target->modelMatrix = globalRotate*trans*objectRotate;
}
