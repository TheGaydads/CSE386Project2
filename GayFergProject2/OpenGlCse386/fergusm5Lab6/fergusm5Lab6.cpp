#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor.h"
#include "Pyramid.h"

class fergusm5Lab6 : public OpenGLApplicationBase
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

	fergusm5Lab6 ()
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
		pyramid1 = new Pyramid();
		pyramid1->setShader(shaderProgram);
		addChild( pyramid1 );
		pyramid2 = new Pyramid();
		pyramid2->setShader(shaderProgram);
		addChild( pyramid2 );
		pyramid3 = new Pyramid();
		pyramid3->setShader(shaderProgram);
		addChild( pyramid3 );
		pyramid4 = new Pyramid();
		pyramid4->setShader(shaderProgram);
		addChild( pyramid4 );
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
		pyramid0->modelMatrix = glm::mat4(1.0f);
		pyramid1->modelMatrix = glm::mat4(1.0f);
		pyramid2->modelMatrix = glm::mat4(1.0f);
		pyramid3->modelMatrix = glm::mat4(1.0f);
		pyramid4->modelMatrix = glm::mat4(1.0f);
	} // end initialize

	// Update scene objects inbetween frames 
	virtual void update( float elapsedTimeSec ) 
	{ 
		static float x = 3.5;
		static float z = 3.5;
		static int leg = 0;
		switch (leg) {
		case 0:
			z-=0.1;
			if (z <= -3.5) {
				leg = 1;
				z = -3.5f;
			}
			break;
		case 1:
			x-=0.1;
			if (x <= -3.5) {
				leg = 2;
				x = -3.5f;
			}
			break;
		case 2:
			z+=0.1;
			if (z >= 3.5) {
				leg = 3;
				z = 3.5;
			}
			break;
		case 3:
			x+=0.1;
			if (x >= 3.5) {
				leg = 0;
				x = 3.5;
			}
			break;
		}
		setViewPoint(); 
		floor->update(elapsedTimeSec);
		static float rotation = 0.0f;
		rotation += elapsedTimeSec * 25.0f;
		glm::mat4 RY = glm::rotate(glm::mat4(1.0f),
			-fmod(rotation, 360.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 RX = glm::rotate(glm::mat4(1.0f), 
			fmod(rotation, 360.0f)*2,
			glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 RZ = glm::rotate(glm::mat4(1.0f), 
			fmod(rotation, 360.0f),
			glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 T1 = glm::translate(glm::mat4(1.0f),
			glm::vec3(3.0f, 0.0f, 0.0f));
		glm::mat4 T2 = glm::translate(glm::mat4(1.0f),
			glm::vec3(-3.0f, 0.0f, 0.0f));
		glm::mat4 T3 = glm::translate(glm::mat4(1.0f),
			glm::vec3(10.0f, 0.0f, 0.0f));
		glm::mat4 SquareT = glm::translate(glm::mat4(1.0f),
			glm::vec3(x, -2.5f, z));
		glm::mat4 S1 = glm::scale(glm::mat4(1.0f),
			glm::vec3( 2.0f, 2.0f, 2.0f));
		pyramid0->modelMatrix = RY;
		pyramid1->modelMatrix = T1*RX;
		pyramid2->modelMatrix = T2*RZ*S1;
		pyramid3->modelMatrix = RY*T3*RX;
		pyramid4->modelMatrix = SquareT;
		VisualObject::update( elapsedTimeSec );
	} // end update

protected:

};

fergusm5Lab6* labClassPtr;

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
	fergusm5Lab6 pApp;
	labClassPtr=&pApp;
	GLUTBaseRunApplication(&pApp);
} // end main