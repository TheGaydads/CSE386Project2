#include "OpenGLApplicationBase.h"
#include "glutbase.h"

/**
* Responds to special key presses. Called by SpecialKeyboardCB in GLUTbase
* which is registered with GLUT by calling glutSpecialFunc.
* @param Key Generated ASCII character for the key whose press triggered the callback.
* @param x x-coordinate of the mouse relative to the window when the key was pressed.
* @param y y-coordinate of the mouse relative to the window when the key was pressed.
*/
static void SpecialKeyboardCB(int Key, int x, int y)
{
cout << "key with ascii code " << Key << " pressed." << endl;
} // end SpecialKeyboardCB
void PassiveMotionFunc(int x, int y)
{
	cout << "mouse motion with button up at (" << x << "," << y << ")" << endl;
}

class fergusm5Lab2 : public OpenGLApplicationBase
{
public:
	fergusm5Lab2 ()
	{
	}

	virtual void initialize()
	{
		glutSpecialFunc(SpecialKeyboardCB);
		glutPassiveMotionFunc(PassiveMotionFunc);
		setupMenus();
		glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
	} // end initialize
	// Render scene objects
	virtual void draw()
	{
	} // end draw
}; // end fergusm5Lab2

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab2" );
	fergusm5Lab2 pApp;
	GLUTBaseRunApplication(&pApp);
} // end main