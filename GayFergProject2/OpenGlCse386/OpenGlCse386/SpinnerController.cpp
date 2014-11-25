#include "SpinnerController.h"

SpinnerController::SpinnerController(glm::vec3 pos, glm::vec3 ax, GLfloat r)
{
	position = pos;
	axis = ax;
	rate = r;
}

void SpinnerController::update(float elapsedTimeSeconds)
{
	static float rotation = 0.0f;
	rotation += elapsedTimeSeconds * rate;

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), fmod(rotation, 360.0f), axis);
	target->modelMatrix = trans*rotate;
}