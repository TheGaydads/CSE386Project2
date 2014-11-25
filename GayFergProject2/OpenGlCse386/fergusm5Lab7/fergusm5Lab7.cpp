#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor.h"
#include "Pyramid.h"
#include "Controller.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"

class fergusm5Lab7 : public OpenGLApplicationBase
{
public:

	Floor* floor;
	Pyramid* pyramid0;
	Pyramid* pyramid1;
	Pyramid* pyramid2;
	Pyramid* pyramid3;
	Pyramid* pyramid4;
	GLint view;
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat changeZ;

	fergusm5Lab7 ()
		:view(0), rotationX(0), rotationY(0), changeZ(-12.0f)
	{
		glutSpecialFunc(SpecialKeyboardCB);
		// Create array of ShaderInfo structs that specifies the vertex and 
		// fragment shaders to be compiled and linked into a program. 
		ShaderInfo shaders[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "pcFS.frag"}, 
			{ GL_NONE, NULL } 
			// signals that there are no more shaders 
		};
		// Read the files and create the OpenGL shader program. 
		GLuint shaderProgram = BuildShaderProgram(shaders);

		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		floor = new Floor();
		floor->setShader(shaderProgram);
		addChild( floor );
		pyramid0 = new Pyramid();
		pyramid0->setShader(shaderProgram);
		addChild( pyramid0 );
		pyramid0->addController(new SpinnerController(glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f), 25.0f));
		pyramid1 = new Pyramid();
		pyramid1->setShader(shaderProgram);
		addChild( pyramid1 );
		pyramid1->addController(new SpinnerController(glm::vec3(3.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f), 25.0f));
		pyramid2 = new Pyramid(2,2);
		pyramid2->setShader(shaderProgram);
		addChild( pyramid2 );
		pyramid2->addController(new SpinnerController(glm::vec3(-3.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f), 25.0f));
		pyramid3 = new Pyramid();
		pyramid3->setShader(shaderProgram);
		addChild( pyramid3 );
		pyramid3->addController(new OrbitController(glm::vec3(0.0f, 1.0f, 0.0f), -25.0f, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 25.0f));
		
		vector<glm::vec3> waypoints;
		waypoints.push_back(glm::vec3(3.5f, -2.5f, 3.5f));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, 3.5f));
		
		pyramid4 = new Pyramid();
		pyramid4->setShader(shaderProgram);
		addChild( pyramid4 );
		pyramid4->addController(new WaypointController(waypoints, 2.0f));
	}

	friend void SpecialKeyboardCB(int Key, int x, int y);
	friend void viewMenu(int value);

	void KeyboardCB(unsigned char Key, int x, int y)
	{
		switch (Key) {
		case 'w':
			changeZ++;
			break;
		case 's':
			changeZ--;
			break;
		case '1':
			if (pyramid0->getParent() == NULL ) {
				this->addChild(pyramid0);
			}
			else {
				pyramid0->detachFromParent();
			}
			break;
		case '2':
			if (pyramid1->getParent() == NULL ) {
				this->addChild(pyramid1);
			}
			else {
				pyramid1->detachFromParent();
			}
			break;
		case '3':
			if (pyramid2->getParent() == NULL ) {
				this->addChild(pyramid2);
			}
			else {
				pyramid2->detachFromParent();
			}
			break;
		case '4':
			if (pyramid3->getParent() == NULL ) {
				this->addChild(pyramid3);
			}
			else {
				pyramid3->detachFromParent();
			}
			break;
		case '5':
			if (pyramid4->getParent() == NULL ) {
				this->addChild(pyramid4);
			}
			else {
				pyramid4->detachFromParent();
			}
			break;
		default:
			OpenGLApplicationBase::KeyboardCB (Key, x, y);
			break;
		}} // end SpecialKeyboardCB

	GLuint createViewMenu()
	{
		GLuint menuId = glutCreateMenu(viewMenu);
		// Specify menu items and their integer identifiers
		glutAddMenuEntry("Default", 0);
		glutAddMenuEntry("View 1", 1);
		glutAddMenuEntry("View 2", 2);
		glutAddMenuEntry("View 3", 3);
		glutAddMenuEntry("View 4", 4);
		glutAddMenuEntry("View 5", 5);
		glutAddMenuEntry("View 6", 6);
		glutAddMenuEntry("View 7", 7);

		return menuId;
	}

	void setUpMenus()
	{
		// Create polygon submenu
		GLuint menu0id = createViewMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliasMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("View", menu0id); // Attach View Menu
		glutAddSubMenu("Polygon Mode", menu1id);
		glutAddSubMenu("Rendered Polygon Face", menu2id);
		glutAddSubMenu("Point Size", menu3id);
		glutAddSubMenu("Line Width", menu4id);
		glutAddSubMenu("Anti-aliasing", menu5id);
		glutAddMenuEntry("Quit", 1); //Quit identifier.
		glutAttachMenu(GLUT_RIGHT_BUTTON);//Menu responds to right button
	}
	virtual void draw()
	{
		GLuint windowWidth = glutGet(GLUT_WINDOW_WIDTH );
		GLuint windowHeight= glutGet(GLUT_WINDOW_HEIGHT );
		glViewport(0, 0, windowWidth/2, windowHeight);
		projectionAndViewing.setProjectionMatrix(glm::perspective(45.0f, (GLfloat)(windowWidth/2)/windowHeight, 0.1f, 100.0f));
		VisualObject::draw();
		glViewport(windowWidth/2, 0, windowWidth/2, windowHeight);
		projectionAndViewing.setProjectionMatrix(glm::ortho(-3.5f, 3.5f, -5.0f, 5.0f, 0.1f, 100.0f));
		
		VisualObject::draw();
	}

	void setViewPoint( )
	{
		glm::mat4 viewMatrix;
		glm::mat4 T12 = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -12));
		glm::mat4 T10 = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -10));
		glm::mat4 R45 = glm::rotate(glm::mat4(1.0f), 45.0f, 
			glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 R90 = glm::rotate(glm::mat4(1.0f), 90.0f, 
			glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 R90Y = glm::rotate(glm::mat4(1.0f), 90.0f, 
			glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 transView;
		glm::mat4 rotateViewX;
		glm::mat4 rotateViewY;
		static float rotation = 0.0f;
		switch (view) {
		case 0:
			projectionAndViewing.setViewMatrix(T12);
			break;
		case 1:
			projectionAndViewing.setViewMatrix(T10);
			break;
		case 2:		
			projectionAndViewing.setViewMatrix(T10*R45);
			break;
		case 3:		
			projectionAndViewing.setViewMatrix(T10*R90*R90Y);
			break;
		case 4:
			viewMatrix = glm::lookAt(glm::vec3( 0.0f, 0.0f, 10.0f ),
				glm::vec3( 0.0f, 0.0f, 0.0f),
				glm::vec3( 0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 5:
			viewMatrix = glm::lookAt(glm::vec3( 0.0f, 10*sin(glm::radians(45.0f)), 10*cos(glm::radians(45.0f))),
				glm::vec3( 0.0f, 0.0f, 0.0f),
				glm::vec3( 0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 6:
			viewMatrix = glm::lookAt(glm::vec3( 0.0f, 10.0f, 0.0f ),
				glm::vec3( 0.0f, 0.0f, 0.0f),
				glm::vec3( 1.0f, 0.0f, 0.0f));
			projectionAndViewing.setViewMatrix(viewMatrix);
			break;
		case 7:
			transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f,changeZ ));
			rotateViewX = glm::rotate(glm::mat4(1.0f), rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
			rotateViewY = glm::rotate(glm::mat4(1.0f), rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
			projectionAndViewing.setViewMatrix( transView * rotateViewX * rotateViewY );
			break;
		default:
			cout << "Invalid view selected." << endl;
			break;
		}
	}

	virtual void initialize()
	{
		glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();

		VisualObject::initialize();
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
	} // end initialize

	// Update scene objects inbetween frames 
	virtual void update( float elapsedTimeSec ) 
	{ 
		setViewPoint(); 
		floor->update(elapsedTimeSec);		
		VisualObject::update( elapsedTimeSec );
	} // end update

protected:

};

fergusm5Lab7* labClassPtr;

// put special key out here for arrows and normal key in class for wasd.
static void SpecialKeyboardCB(int Key, int x, int y)
{
	switch (Key) {
	case GLUT_KEY_RIGHT:
		labClassPtr->rotationY--;
		break;
	case GLUT_KEY_LEFT:
		labClassPtr->rotationY++;
		break;
	case GLUT_KEY_UP:
		labClassPtr->rotationX++;
		break;
	case GLUT_KEY_DOWN:
		labClassPtr->rotationX--;
		break;
	default:
		break;
	}
}

void viewMenu (int value)
{
	labClassPtr->view = value;
	cout << "View point " << value << endl;
} // end viewMenu

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 6" );
	fergusm5Lab7 pApp;
	labClassPtr=&pApp;
	GLUTBaseRunApplication(&pApp);
} // end main