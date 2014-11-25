#include "OpenGLApplicationBase.h"
#include "glutbase.h"
#include "Floor.h"
#include "Pyramid.h"

class fergusm5Lab5 : public OpenGLApplicationBase
{
public:

	Floor* floor;
	Pyramid* pyramid0;
	Pyramid* pyramid1;
	Pyramid* pyramid2;
	Pyramid* pyramid3;
	Pyramid* pyramid4;

	fergusm5Lab5 ()
	{
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
		pyramid0 = new Pyramid();
		pyramid0->setShader(shaderProgram);
		pyramid1 = new Pyramid();
		pyramid1->setShader(shaderProgram);
		pyramid2 = new Pyramid();
		pyramid2->setShader(shaderProgram);
		pyramid3 = new Pyramid();
		pyramid3->setShader(shaderProgram);
		pyramid4 = new Pyramid();
		pyramid4->setShader(shaderProgram);
	}

	~fergusm5Lab5()
	{
		delete floor;
		delete pyramid0;
		delete pyramid1;
		delete pyramid2;
		delete pyramid3;
		delete pyramid4;
	}

	virtual void initialize()
	{
		glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable( GL_DEPTH_TEST );
		setupMenus();

		floor->initialize();
		floor->modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		pyramid0->initialize();
		pyramid0->modelMatrix = glm::mat4(1.0f);
		pyramid1->initialize();
		pyramid1->modelMatrix = glm::mat4(1.0f);
		pyramid2->initialize();
		pyramid2->modelMatrix = glm::mat4(1.0f);
		pyramid3->initialize();
		pyramid3->modelMatrix = glm::mat4(1.0f);
		pyramid4->initialize();
		pyramid4->modelMatrix = glm::mat4(1.0f);
		//pyramid0->modelMatrix = glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	} // end initialize

	// Render scene objects
	virtual void draw()
	{
		floor->draw();
		pyramid0->draw();
		pyramid1->draw();
		pyramid2->draw();
		pyramid3->draw();
		pyramid4->draw();
	} // end draw

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
		pyramid0->update(elapsedTimeSec);
		pyramid1->modelMatrix = T1*RX;
		pyramid1->update(elapsedTimeSec);
		pyramid2->modelMatrix = T2*RZ*S1;
		pyramid2->update(elapsedTimeSec);
		pyramid3->modelMatrix = RY*T3*RX;
		pyramid3->update(elapsedTimeSec);
		pyramid4->modelMatrix = SquareT;
		pyramid4->update(elapsedTimeSec);
	} // end update

protected:

};

int main(int argc, char** argv)
{
	GLUTBaseInit(argc, argv);
	GLUTBaseCreateWindow( "CSE 386 Lab 5" );
	fergusm5Lab5 pApp;
	GLUTBaseRunApplication(&pApp);
} // end main