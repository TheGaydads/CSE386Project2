#include "Controller.h"

class WaypointController : public Controller
{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	WaypointController(vector<glm::vec3> waypoints, float speed);
	virtual void update(float elapsedTimeSeconds);
	float distanceToTargetWaypoint();
	int getNextWaypointIndex();
	void updateVelocityForWaypoint();
protected:
	vector<glm::vec3> waypoints;
	GLfloat speed;
	glm::vec3 position;
	glm::vec3 velocity;
	int waypointIndex;
};