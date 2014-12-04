#pragma once
#include "BallisticsController.h"

using namespace glm;

BallisticsController::BallisticsController(glm::vec3 position) {
	this->velocity = normalize(vec3(0.0f, -1.0f, 0.0f)) * 4.2f;
	this->position = position;
	gravity = vec3 (0.0f, -4.2f, 0.0f);
}

BallisticsController::~BallisticsController(void) {

}

void BallisticsController::update(float elapsedTimeSeconds) {

	velocity += (gravity * elapsedTimeSeconds * 0.5f);
	position += (velocity * elapsedTimeSeconds * 0.5f);
	
	target->modelMatrix = translate(mat4(1.0f), position);
	//* translate(mat4(1.0f), vec3(0.0f, -4.0f, 12.0f));
}

