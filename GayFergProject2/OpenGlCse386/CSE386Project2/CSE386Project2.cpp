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
#include "BallisticsController.h"
#include "font.h"
#include <time.h>
#include "Target.h"
#include "Cloud.h"
#include "Snowman.h"

class CSE386Project2 : public OpenGLApplicationBase
{
public:

	Tree* tree;
	Wall* floor;
	GLint view;
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat changeZ;
	GLfloat changeX;
	SharedGeneralLighting generalLighting;
	SoundSource* sound;
	Cube* basket;
	PlayerController* playerController;
	vector<VisualObject*> snowballs;
	vector<VisualObject*> coals;
	vector<VisualObject*> clouds;
	vector<VisualObject*> targets;
	GLuint shaderProgram;
	Sphere* snowball;
	Sphere* coal;
	Target* target;
	Cloud* cloud;
	Snowman* snowman;
	int snowballsCaught;
	int coalHit;
	float gameClock;
	bool isView1;

	CSE386Project2()
		:view(0), rotationX(0), rotationY(0), changeZ(-8.0f), changeX(0.0f), snowballsCaught(0), coalHit(5), gameClock(0.0f), isView1(false)
	{
		//redundant

		srand ( time(0) );
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
		shaderProgram = BuildShaderProgram(shaders);

		projectionAndViewing.setUniformBlockForShader(shaderProgram);
		generalLighting.setUniformBlockForShader( shaderProgram );

		floor = new Wall(); 
		//wall->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, -4.0f)); 
		floor->fixedTransformation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 6.0f)) * rotate(mat4(1.0f), -90.0f, vec3(1.0f, 0.0f, 0.0f));
		floor->material.setAmbientMat(vec4(0.0f, 0, 0.0f, 0.0f));
		floor->setShader(shaderProgram); 
		floor->material.setTextureMapped(true); 
		floor->material.setupTexture("snow.bmp"); 
		addChild(floor);

		tree = new Tree(); 
		tree->fixedTransformation = translate(mat4(1.0f), vec3(0.0f, -3.0f, -4.0f)); 
		tree->setShader(shaderProgram); 
		tree->material.setTextureMapped(true); 
		tree->material.setupTexture("snowBackground.bmp"); 
		addChild(tree);

		
		sound = new SoundSource("skating.wav"); 
		sound->setLooping(true); 
		this->addChild(sound);
		sound->play();
		

		vector<glm::vec3> waypoints;
		waypoints.push_back(glm::vec3(3.5f, -2.5f, 3.5f));
		waypoints.push_back(glm::vec3(3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, -3.5f));
		waypoints.push_back(glm::vec3(-3.5f, -2.5f, 3.5f));

		basket = new Cube();
		basket->setShader(shaderProgram);
		basket->material.setAmbientAndDiffuseMat(vec4(0.0f, 1.0f, 0.0f, 1.0f));
		basket->material.setTextureMapped(true); 
		basket->material.setupTexture("Basket.bmp"); 
		addChild(basket);
		basket->addController(playerController = new PlayerController());

		snowman = new Snowman();
		snowman->setShader( shaderProgram );
		snowman->modelMatrix = translate(mat4(1.0f), vec3(-2.0f, -2.7f, 3.0f)) * rotate(mat4(1.0f), 30.0f, vec3(0.0f, 1.0f, 0.0f)); 
		addChild(snowman);
		

		setupLighting(shaderProgram);
	}

	void draw() {
		screenTextOutput (70, 75, "Snowballs Caught: " + to_string(snowballsCaught) + (string)"", vec4(0.0f, 0.0f, 0.0f, 1.0f));
		screenTextOutput (70, 100, "Life Left: " + to_string(coalHit) + (string)"", vec4(0.0f, 0.0f, 0.0f, 1.0f));

		VisualObject::draw();
	}

	void addSpawn(int location, int object) 
	{
		switch(object) {
		case(0):
			snowball = new Sphere(0.125f);
			snowball->setShader(shaderProgram);
			snowball->material.setAmbientAndDiffuseMat(vec4(1.0f, 1.0f, 1.0f, 1.0f));
			snowball->modelMatrix = translate(mat4(1.0f), vec3(location, 5.0f, -3.0f));
			snowball->addController(new BallisticsController(snowball->getWorldPosition()));

			addChild(snowball);
			snowball->update(0.0f);
			snowball->initialize();

			snowballs.push_back(snowball);
			break;
		case(1):
			coal = new Sphere(0.125f);
			coal->setShader(shaderProgram);
			coal->material.setAmbientAndDiffuseMat(vec4(0.0f, 0.0f, 0.0f, 1.0f));
			coal->modelMatrix = translate(mat4(1.0f), vec3(location, 5.0f, -3.0f));
			coal->addController(new BallisticsController(coal->getWorldPosition()));

			addChild(coal);
			coal->update(0.0f);
			coal->initialize();

			coals.push_back(coal);
			break;

		case(2):
			cloud = new Cloud();
			cloud->setShader( shaderProgram );
			cloud->modelMatrix = translate(mat4(1.0f), vec3(location-.25, 5.0f, -3.0f))*scale(mat4(1.0f), vec3(0.01f, 0.01f, 0.01f));
			cloud->addController(new BallisticsController(cloud->getWorldPosition()));

			addChild(cloud);
			cloud->update(0.0f);
			cloud->initialize();

			clouds.push_back(cloud);
			break;
		case(3):
			target = new Target();
			target->setShader( shaderProgram );
			target->modelMatrix = translate(mat4(1.0f), vec3(location, 5.0f, -3.0f));
			target->addController(new BallisticsController(target->getWorldPosition()));

			addChild(target);
			target->update(0.0f);
			target->initialize();

			targets.push_back(target);
			break;
		}
	}

	void setupLighting(GLuint shaderProgram)
	{
		// ***** Ambient Light **************
		/*generalLighting.setEnabled( GL_LIGHT_ZERO, true);
		generalLighting.setAmbientColor( GL_LIGHT_ZERO,
			vec4(0.2f, 0.2f, 0.2f, 1.0f));*/

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
			vec4(0.7f, 0.7f, 0.7f, 1.0f) );
		generalLighting.setSpecularColor( GL_LIGHT_THREE,
			vec4(1.0f, 1.0f, 1.0f, 1.0f) );
		generalLighting.setPositionOrDirection( GL_LIGHT_THREE,
			vec4(changeX, 8.0f, -3.0f, 1.0f) );
		generalLighting.setSpotDirection( GL_LIGHT_THREE,
			vec3(0.0f, -1.0f, 0.0f) );
		generalLighting.setSpotCutoffCos( GL_LIGHT_THREE,
			cos(glm::radians(5.0f)) );
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
			/*lightOn = generalLighting.getEnabled( GL_LIGHT_ZERO );
			generalLighting.setEnabled( GL_LIGHT_ZERO, !lightOn );*/
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
			/*	case 'q':
			addApple();
			break;*/
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
		//For Player View
		glm::mat4 playerTranslate = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 1.0f, -8.0f));
		glm::mat4 T24 = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 2.0f, 1.0f));
		glm::mat4 transView;
		glm::mat4 rotateViewX;
		glm::mat4 rotateViewY;
		static float rotation = 0.0f;
		switch (view) {
		case 0:
			projectionAndViewing.setViewMatrix(playerTranslate);
			break;
		case 1:

			transView = glm::translate(glm::mat4(1.0f), glm::vec3( -changeX, 0.0f,changeZ ));

			projectionAndViewing.setViewMatrix( T24* transView );
				break;
		case 7:
			transView = glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 1.0f,changeZ ));
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
		glClearColor(0.0f, 0.7f, 0.9f, 1.0f);
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

		RandomSpawn(elapsedTimeSec);

		float distance = 9999;
		if(snowballs.size() > 0) {
			for (int i = 0; i < snowballs.size(); i++ ) {


				distance = glm::distance(snowballs[i]->getWorldPosition(), basket->getWorldPosition());

				//If apple is in basket, delete apple & add to apples caught counter
				if (distance < 0.1) {

					snowballsCaught++;
					VisualObject* obj = snowballs[i];
					snowballs.erase(snowballs.begin() + i);
					obj->detachFromParent();
					delete obj;
				}

				//If apple below board delete
				else if (snowballs[i]->getWorldPosition().y < -5.0f) {
					VisualObject* obj = snowballs[i];
					snowballs.erase(snowballs.begin() + i);
					obj->detachFromParent();
					delete obj;
				}
			}
		}

		if(coals.size() > 0) {
			for (int i = 0; i < coals.size(); i++ ) {


				distance = glm::distance(coals[i]->getWorldPosition(), basket->getWorldPosition());

				//If apple is in basket, delete apple & add to apples caught counter
				if (distance < 0.1) {

					coalHit--;
					VisualObject* obj = coals[i];
					coals.erase(coals.begin() + i);
					obj->detachFromParent();
					delete obj;
				}

				//If apple below board delete
				else if (coals[i]->getWorldPosition().y < -5.0f) {
					VisualObject* obj = coals[i];
					coals.erase(coals.begin() + i);
					obj->detachFromParent();
					delete obj;
				}
			}
		}

		if(targets.size() > 0) {
			for (int i = 0; i < targets.size(); i++ ) {


				distance = glm::distance(targets[i]->getWorldPosition(), basket->getWorldPosition());

				//If apple is in basket, delete apple & add to apples caught counter
				if (distance < 0.1) {
					if(isView1) {
						view = 0;
						isView1 = false;
					} else {
					view = 1;
					isView1 = true;
					}
					VisualObject* obj = targets[i];
					targets.erase(targets.begin() + i);
					obj->detachFromParent();
					delete obj;
				}

				//If apple below board delete
				else if (targets[i]->getWorldPosition().y < -5.0f) {
					VisualObject* obj = targets[i];
					targets.erase(targets.begin() + i);
					obj->detachFromParent();
					delete obj;
				}
			}
		}

		generalLighting.setPositionOrDirection( GL_LIGHT_THREE,
			vec4(changeX, 8.0f, -3.0f, 1.0f) );
		setViewPoint(); 
		listenerUpdate(elapsedTimeSec);
		//floor->update(elapsedTimeSec);		
		VisualObject::update( elapsedTimeSec );
	} // end update

protected:

	/**
	*Spawns apple at random time between 3 - 8 second intervals
	*/
	void RandomSpawn(float elapsedTimeSeconds) {
		float randomSpawnTime = rand()%5+3;
		int randomLocation = rand()%10-5;
		int randomObject = rand()%4;

		if (gameClock > randomSpawnTime || gameClock == 0.0f) {
			addSpawn(randomLocation, randomObject);
			gameClock = 0.0f;
		}
		gameClock+=elapsedTimeSeconds;
	}
};

CSE386Project2* labClassPtr;

// put special key out here for arrows and normal key in class for wasd.
static void SpecialKeyboardCB(int Key, int x, int y)
{
	switch (Key) {
	case GLUT_KEY_RIGHT:
		labClassPtr->rotationY--;
		labClassPtr->changeX++;
		if (labClassPtr->changeX > 5.0f) {
			labClassPtr->changeX--;
		}
		labClassPtr->playerController->setXPosition(labClassPtr->changeX);
		break;
	case GLUT_KEY_LEFT:
		labClassPtr->rotationY++;
		labClassPtr->changeX--;
		if (labClassPtr->changeX < -5.0f) {
			labClassPtr->changeX++;
		}
		labClassPtr->playerController->setXPosition(labClassPtr->changeX);
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
	//In order to get random numbers
	srand ( time(0) );

	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "Apples!!!" );
	CSE386Project2 pApp;
	labClassPtr=&pApp;
	GLUTBaseRunApplication(&pApp);
} // end main