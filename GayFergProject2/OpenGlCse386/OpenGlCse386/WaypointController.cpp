#include "WaypointController.h"

WaypointController::WaypointController(vector<glm::vec3> wayP, float s)
{
	waypoints = wayP;
	speed = s;
	position = waypoints[0];
	waypointIndex = 0;
	velocity = speed * glm::normalize(waypoints[1] - waypoints[0]);
}
void WaypointController::update(float elapsedTimeSeconds)
{
	if (distanceToTargetWaypoint() < (speed * elapsedTimeSeconds) ) {
	position = waypoints[getNextWaypointIndex()];
	waypointIndex = getNextWaypointIndex();
	updateVelocityForWaypoint();
	
	}

	position = position + velocity * elapsedTimeSeconds;
	target->modelMatrix = glm::translate(glm::mat4(1.0f), position);	
} // end update

float WaypointController::distanceToTargetWaypoint() 
{
	return glm::distance(waypoints[getNextWaypointIndex()], position);
}

int WaypointController::getNextWaypointIndex()
{
	return (waypointIndex+1) % waypoints.size();
}

void WaypointController::updateVelocityForWaypoint()
{
	velocity = speed * glm::normalize(waypoints[getNextWaypointIndex()] - position);
}

