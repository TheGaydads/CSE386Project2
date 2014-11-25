#include "AttackingObjectsController.h"

AttackingObjectsController::AttackingObjectsController(vector<glm::vec3> wayP, float s) : state(0), hasReachedEnd(false)
{
	waypoints = wayP;
	speed = s;
	position = waypoints[0];
	waypointIndex = 0;
	velocity = speed * glm::normalize(waypoints[1] - waypoints[0]);

}
void AttackingObjectsController::update(float elapsedTimeSeconds)
{
	if (distanceToTargetWaypoint() < (speed * elapsedTimeSeconds) && !hasReachedEnd) {
		position = waypoints[getNextWaypointIndex()];
		waypointIndex = getNextWaypointIndex();
		updateVelocityForWaypoint();
		position = waypoints[getNextWaypointIndex()];
		state = 1;
		hasReachedEnd = true;
	}
	else if (!hasReachedEnd) {
		position = position + velocity * elapsedTimeSeconds;
		target->modelMatrix = glm::translate(glm::mat4(1.0f), position);
	}
} // end update

float AttackingObjectsController::distanceToTargetWaypoint() 
{
	return glm::distance(waypoints[getNextWaypointIndex()], position);
}

int AttackingObjectsController::getNextWaypointIndex()
{
	return (waypointIndex+1) % waypoints.size();
}

void AttackingObjectsController::updateVelocityForWaypoint()
{
	velocity = speed * glm::normalize(waypoints[getNextWaypointIndex()] - position);
}
