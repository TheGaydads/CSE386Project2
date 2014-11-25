#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Tree.h"
#include "Pyramid.h"
#include "Controller.h"
#include "SpinnerController.h"
#include "OrbitController.h"
#include "WaypointController.h"
#include "Wall.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Cube.h"
#include "SpaceShip.h"
#include "SharedGeneralLighting.h"
#include "Wall.h"
#include "SoundSource.h"
#include "PlayerController.h"

class CSE386Project2 : public OpenGLApplicationBase
{
public:

	Tree* tree;
	Wall* grass;
	GLint view;
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat changeZ;
	SharedGeneralLighting generalLighting;
	SoundSource* sound;

	CSE386Project2()
		:view(0), rotationX(0), rotationY(0), changeZ(-12.0f)
	{
		

		glutSpecialFunc(SpecialKeyboardCB);
		// Create array of ShaderInfo structs that specifies the vertex and 
		// fragment shaders to be compiled and linked into a program. 
		ShaderInfo shaders[] = { 
			{ GL_VERTEX_SHADER, "pcVsUniViewProj.vert" }, 
			{ GL_FRAGMENT_SHADER, "psTex.frag"}, 
			{ GL_NONE, NULL } 
			// signals that there are no more shaders 
		};
		// Read the files and create the OpenGL shader program. 
		GLuint shaderProgram = BuildShaderProgram(shaders);

		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader( shaderProgram );

		grass = new Wall(); 
		//wall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, -4.0f)); 
		grass->fixedTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 6.0f)) * rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));

		grass->setShader(shaderProgram); 
		grass->material.setTextureMapped(true); 
		grass->material.setupTexture("grass.bmp"); 
		addChild(grass);
		
		tree = new Tree(); 
		tree->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, -4.0f)); 
		tree->setShader(shaderProgram); 
		tree->material.setTextureMapped(true); 
		tree->material.setupTexture("BlueSky.bmp"); 
		addChild(tree);

		/*
		sound = new SoundSource("Footsteps.wav"); 
		sound->setLooping(true); 
		this->addChild(sound);
		*/

		vector<glm::vec3> waypoints;
		waypoints.push_back(glm::vec3(3.5f, -2.5f, 3.5f));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, 3.5f));

		Cube* cube = new Cube();
		cube->setShader(shaderProgram);
		cube->material.setAmbientAndDiffuseMat(vec4(0.0f, 1.0f, 0.0f, 1.0f));
		cube->material.setTextureMapped(true); 
		cube->material.setupTexture("Basket.bmp"); 
		addChild(cube);
		cube->addController(new PlayerController());

		setupLighting(shaderProgram);
	}

	void setupLighting(GLuint shaderProgram)
	{
		// ***** Ambient Light **************
		generalLighting.setEnabled( GL_LIGHT_ZERO, true);
		generalLighting.setAmbientColor( GL_LIGHT_ZERO,
		vec4(0.2f, 0.2f, 0.2f, 1.0f));

		// ***** Directional Light ****************
		generalLighting.setEnabled( GL_LIGHT_ONE, true);
		generalLighting.setDiffuseColor( GL_LIGHT_ONE,
		vec4(0.75f, 0.75f, 0.75f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_ONE,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_ONE,
		vec4(1.0f, 1.0f, 1.0f, 0.0f) );

		// ***** Positional Light ***************
		generalLighting.setEnabled( GL_LIGHT_TWO, true);
		generalLighting.setDiffuseColor( GL_LIGHT_TWO,
		vec4(0.5f, 0.5f, 0.5f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_TWO,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_TWO,
		vec4(1.0f, 3.0f, 1.0f, 1.0f) );

		// ***** Spot Light **************
		generalLighting.setEnabled( GL_LIGHT_THREE, true );
		generalLighting.setIsSpot( GL_LIGHT_THREE, true );
		generalLighting.setDiffuseColor( GL_LIGHT_THREE,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_THREE,
		vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_THREE,
		vec4(0.0f, 8.0f, 0.0f, 1.0f) );
		generalLighting.setSpotDirection( GL_LIGHT_THREE,
		vec3(0.0f, -1.0f, 0.0f) );
		generalLighting.setSpotCutoffCos( GL_LIGHT_THREE,
		cos(glm::radians(15.0f)) );
	}

	friend void SpecialKeyboardCB(int Key, int x, int y);
	friend void viewMenu(int value);

	void KeyboardCB(unsigned char Key, int x, int y)
	{
		bool lightOn;
		bool soundOn;

		switch (Key) {
		case 'w':
			changeZ++;
			break;
		case 's':
			changeZ--;
			break;
		case 'a':
			lightOn = generalLighting.getEnabled( GL_LIGHT_ZERO );
			generalLighting.setEnabled( GL_LIGHT_ZERO, !lightOn );
			break;
		case 'd':
			lightOn = generalLighting.getEnabled( GL_LIGHT_ONE);
			generalLighting.setEnabled( GL_LIGHT_ONE, !lightOn );
			break;
		case 'p':
			lightOn = generalLighting.getEnabled( GL_LIGHT_TWO );
			generalLighting.setEnabled( GL_LIGHT_TWO, !lightOn );
			break;
		case 'l':
			lightOn = generalLighting.getEnabled( GL_LIGHT_THREE );
			generalLighting.setEnabled( GL_LIGHT_THREE, !lightOn );
			break;
		case 'f': 
			soundOn = !sound->isPlaying(); 
			if (soundOn) { 
				sound->play(); 
			} else { 
				sound->pause(); 
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
	/*virtual void draw()
	{
	GLuint windowWidth = glutGet(GLUT_WINDOW_WIDTH );
	GLuint windowHeight= glutGet(GLUT_WINDOW_HEIGHT );
	glViewport(0, 0, windowWidth/2, windowHeight);
	projectionAndViewing.setProjectionMatrix(glm::perspective(45.0f, (GLfloat)(windowWidth/2)/windowHeight, 0.1f, 100.0f));
	VisualObject::draw();
	glViewport(windowWidth/2, 0, windowWidth/2, windowHeight);
	projectionAndViewing.setProjectionMatrix(glm::ortho(-3.5f, 3.5f, -5.0f, 5.0f, 0.1f, 100.0f));

	VisualObject::draw();
	}*/

	void setViewPoint( )
	{
		glm::mat4 viewMatrix;
		//For Player View
		glm::mat4 playerTranslate = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 1.0f, -8.0f));

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
			projectionAndViewing.setViewMatrix(playerTranslate);
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
		glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();

		VisualObject::initialize();
		
	} // end initialize

	// Set the position, orientation and velocity of the listener 
	virtual void listenerUpdate( float elapsedTimeSec ) { 
		// Get the position of the viewpoint 
		mat4 viewMatrix = projectionAndViewing.getViewMatrix(); 
		vec3 viewPosition = inverse(viewMatrix)[3].xyz;
		// Initilize the "previous view position" for velocity calculations 
		static vec3 lastViewPosition = viewPosition;
		// Determine the orientation of the listener 
		vec3 viewDirection = (viewMatrix * vec4(0.0, 0.0, -1.0, 0.0)).xyz; 
		vec3 viewUp = (viewMatrix * vec4(0.0, 1.0, 0.0, 0.0)).xyz;
		// Set the listener postion 
		alListener3f(AL_POSITION, viewPosition.x, viewPosition.y, viewPosition.z );
		// Set the listener orientation 
		float orientation[] = { viewDirection.x, viewDirection.y, viewDirection.z, viewUp.x, viewUp.y, viewUp.z }; 
		alListenerfv(AL_ORIENTATION, orientation );
		// Set listener velocity 
		if (elapsedTimeSec > 0) {
			vec3 speed = (viewPosition - lastViewPosition)/elapsedTimeSec;
			alListener3f(AL_VELOCITY, speed.x, speed.y, speed.z ); 
		}
		// Save the position for the next listener update. 
		lastViewPosition = viewPosition;
} // end listenerUpdate

	// Update scene objects inbetween frames 
	virtual void update( float elapsedTimeSec ) 
	{ 
		setViewPoint(); 
		listenerUpdate(elapsedTimeSec);
		//grass->update(elapsedTimeSec);		
		VisualObject::update( elapsedTimeSec );
	} // end update

protected:
	
};

CSE386Project2* labClassPtr;

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
	GLUTBaseCreateWindow( "Apples!!!" );
	CSE386Project2 pApp;
	labClassPtr=&pApp;
	GLUTBaseRunApplication(&pApp);
} // end main