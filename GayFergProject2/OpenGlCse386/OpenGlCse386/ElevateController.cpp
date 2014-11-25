#include "ElevateController.h"

void specialKeyCB(int key, int x, int y)
{
	switch(key){
		case GLUT_KEY_UP:
			ep->elevationAngle++;
			break;
		case GLUT_KEY_DOWN:
			ep->elevationAngle--;
			break;
	}

}
ElevateController::ElevateController()
	:elevationAngle(0.0f), direction(0.0f, 0.0f, -1.0f, 1.0f)
{
	ep = this;
	glutSpecialFunc(specialKeyCB);
}

// Sample update method for demonstration purposes.
void ElevateController::update(float elapsedTimeSeconds)
{
	target->modelMatrix = glm::rotate(glm::mat4(1.0f), elevationAngle, glm::vec3(1,0,0));

	direction =  glm::rotate(glm::mat4(1.0f), elevationAngle, glm::vec3(1,0,0))*glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
} // end update
 
