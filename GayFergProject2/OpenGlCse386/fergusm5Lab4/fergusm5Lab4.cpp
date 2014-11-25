#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "ColoredThreeTriangleFigure.h"
#include "InLvColoredThreeTriangleFigure.h"
#include "FourPointedStarFigure.h"

class fergusm5Lab3 : public OpenGLApplicationBase
{
public:
	fergusm5Lab3 ()
		: figure(1)
	{
		// Create array of ShaderInfo structs that specifies the vertex and
		// fragment shaders to be compiled and linked into a program.
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "pcVS.vert" },
			{ GL_FRAGMENT_SHADER, "pcFS.frag"},
			{ GL_NONE, NULL } // signals that there are no more shaders
		};
		// Read the files and create the OpenGL shader program.
		GLuint shaderProgram = BuildShaderProgram(shaders);

		fig1.setShader(shaderProgram);
		fig2.setShader(shaderProgram);
		fig3.setShader(shaderProgram);
	}

	virtual void initialize()
	{
		glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable( GL_DEPTH_TEST );
		setUpMenus();
		fig1.initialize();
		fig2.initialize();
		fig3.initialize();
	} // end initialize

	// Render scene objects
	virtual void draw()
	{
		switch( figure ) {
		case 1:
			fig1.draw();
			break;
		case 2:
			fig2.draw();
			break;
		case 3:
			fig3.draw();
			break;
		default:
			cout << "Invalid figure selected." << endl;
			break;
		}
	} // end draw

	friend void figureMenu(int value);

	GLuint createFigureMenu()
	{
		GLuint menuId = glutCreateMenu(figureMenu);
		// Specify menu items and their integer identifiers
		glutAddMenuEntry("Figure 1", 1);
		glutAddMenuEntry("Figure 2", 2);
		glutAddMenuEntry("Figure 3", 3);

		return menuId;
	}

	void setUpMenus()
	{
		// Create polygon submenu
		GLuint menu0id = createFigureMenu();
		GLuint menu1id = createPolygonMenu();
		GLuint menu2id = createFrontFaceMenu();
		GLuint menu3id = createPointSizeMenu();
		GLuint menu4id = createLineWidthMenu();
		GLuint menu5id = createAntiAliasMenu();
		// Create main menu
		topMenu = glutCreateMenu(mainMenu);
		glutAddSubMenu("Figure", menu0id); // Attach polygon Menu
		glutAddSubMenu("Polygon Mode", menu1id);
		glutAddSubMenu("Rendered Polygon Face", menu2id);
		glutAddSubMenu("Point Size", menu3id);
		glutAddSubMenu("Line Width", menu4id);
		glutAddSubMenu("Anti-aliasing", menu5id);
		glutAddMenuEntry("Quit", 1); //Quit identifier.
		glutAttachMenu(GLUT_RIGHT_BUTTON);//Menu responds to right button
	}

protected:
	GLint figure;
	ColoredThreeTriangleFigure fig1;
	InLvColoredThreeTriangleFigure fig2;
	FourPointedStarFigure fig3;
}; // end uniqueidLab3

fergusm5Lab3* classPtr;

void figureMenu(int value)
{
	(classPtr)->figure = value;
	cout << "Drawing figure " << value << endl;
} // end figureMenu

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 4" );
	fergusm5Lab3 pApp;
	classPtr = &pApp;
	GLUTBaseRunApplication(&pApp);

} // end main