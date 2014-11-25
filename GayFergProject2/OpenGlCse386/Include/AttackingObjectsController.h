#include "Controller.h"

class AttackingObjectsController : public Controller
{
public:
	// Constructor sets the position of the object,
	// the axis about which it will rotate, and the rate and direction
	// of rotation.
	AttackingObjectsController(vector<glm::vec3> waypoints, float speed);
	virtual void update(float elapsedTimeSeconds);
	float distanceToTargetWaypoint();
	int getNextWaypointIndex();
	void updateVelocityForWaypoint();
	int state;
	bool hasReachedEnd;
protected:
	vector<glm::vec3> waypoints;
	GLfloat speed;
	glm::vec3 position;
	glm::vec3 velocity;
	int waypointIndex;

};