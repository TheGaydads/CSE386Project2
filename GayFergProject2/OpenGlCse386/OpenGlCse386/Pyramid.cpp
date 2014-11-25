#include "Pyramid.h"
#include "Material.h"
#include "vertexStructs.h"
#include "textureCoordinates.h"

/**
* Constructor for the Pyramid class. Created a visual object in the shape of a pyramid. Vertex
* positions are expressed relative to an origin that is located in the center of the pyramid.
* @param OpenGLApp - reference to the OpenGLApplicationBase object that holds the projection
*        and viewing transformations
* @param w - width of the base of the pyramid. Default is 1 unit.
* @param h - height of the pyramid. Default is 1 unit.
*/
Pyramid::Pyramid( GLfloat w, GLfloat h)
{
	width=w;
	height=h;
}

/**
* Builds shader program and initializes vertex array object that will be used to render the 
* the object.
*/
void Pyramid::initialize()
{
	setShaderValues();
	/*modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	assert(modelLocation != 0xFFFFFFFF);*/
	GLuint VBO;
	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );
	vec3 v0 = vec3(width/2, -height/2, width/2); 
	vec3 v1 = vec3(width/2, -height/2, -width/2); 
	vec3 v2 = vec3(-width/2, -height/2, -width/2); 
	vec3 v3 = vec3(-width/2, -height/2, width/2); 
	vec3 v4 = vec3(0.0f, height/2, 0.0f);

	vector<pntVertexData> v;

	//Front face 
	vec3 frontFaceNormal = findUnitNormal(v0, v4, v3); 
	vec4 frontFaceColor(1.0f, 0.0f, 0.5f, 1.0f);
	v.push_back(pntVertexData(v0, frontFaceNormal, getPlanarTextCoords(v0, width, height))); 
	v.push_back(pntVertexData(v4, frontFaceNormal, getPlanarTextCoords(v4, width, height))); 
	v.push_back(pntVertexData(v3, frontFaceNormal, getPlanarTextCoords(v3, width, height)));

	//Right face
	vec3 rightFaceNormal = findUnitNormal(v1, v4, v0); 
	vec4 rightFaceColor(0.0f, 1.0f, 0.0f, 1.0f);
	v.push_back(pntVertexData(v1, rightFaceNormal, getPlanarTextCoords(v1, width, height)));
	v.push_back(pntVertexData(v4, rightFaceNormal, getPlanarTextCoords(v4, width, height)));
	v.push_back(pntVertexData(v0, rightFaceNormal, getPlanarTextCoords(v0, width, height)));

	//Back face
	vec3 backFaceNormal = findUnitNormal(v2, v4, v1); 
	vec4 backFaceColor(1.0f, 0.5f, 0.0f, 1.0f);
	v.push_back(pntVertexData(v2, backFaceNormal, getPlanarTextCoords(v2, width, height)));
	v.push_back(pntVertexData(v4, backFaceNormal, getPlanarTextCoords(v4, width, height)));
	v.push_back(pntVertexData(v1, backFaceNormal, getPlanarTextCoords(v1, width, height)));

	//Left face
	vec3 leftFaceNormal = findUnitNormal(v2, v3, v4); 
	vec4 leftFaceColor(0.0f, 1.0f, 1.0f, 1.0f);
	v.push_back(pntVertexData(v2, leftFaceNormal, getPlanarTextCoords(v2, width, height)));
	v.push_back(pntVertexData(v3, leftFaceNormal, getPlanarTextCoords(v3, width, height))); 
	v.push_back(pntVertexData(v4, leftFaceNormal, getPlanarTextCoords(v4, width, height)));

	//Bottom faces
	vec3 bottomFaceNormal = vec3(0.0f, -1.0f, 0.0f); 
	vec4 bottomFaceColor(0.0f, 0.0f, 0.6f, 1.0f);
	v.push_back(pntVertexData(v0, bottomFaceNormal, getPlanarTextCoords(v0, width, height)));
	v.push_back(pntVertexData(v3, bottomFaceNormal, getPlanarTextCoords(v3, width, height)));
	v.push_back(pntVertexData(v2, bottomFaceNormal, getPlanarTextCoords(v2, width, height)));
	v.push_back(pntVertexData(v0, bottomFaceNormal, getPlanarTextCoords(v0, width, height)));
	v.push_back(pntVertexData(v2, bottomFaceNormal, getPlanarTextCoords(v2, width, height)));
	v.push_back(pntVertexData(v1, bottomFaceNormal, getPlanarTextCoords(v1, width, height)));

	glGenBuffers(1, &VBO);
	glBindBuffer( GL_ARRAY_BUFFER, VBO);
	glBufferData( GL_ARRAY_BUFFER, v.size() * sizeof(pncVertexData), &v[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE,sizeof(pntVertexData),(const GLvoid*)sizeof(glm::vec3));
	glEnableVertexAttribArray(1);
	/*glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE,sizeof(pntVertexData),(const GLvoid*)(sizeof(glm::vec3)*2));
	glEnableVertexAttribArray(2);*/
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(pntVertexData), (const GLvoid*)(2 * sizeof(vec3)) ); 
	glEnableVertexAttribArray(3);

	// Initialize all children
	VisualObject::initialize();
}// end initialize

/*
* Renders the object using the visual object using the vertex array object that was created by
* the initialize method.
*/
void Pyramid::draw()
{
	glUseProgram(shaderProgram);
	/*glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelAndFixed));
	glBindVertexArray(vertexArrayObject);*/
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(modelMatrix));
	glBindVertexArray(vertexArrayObject);
	material.setShaderMaterialProperties();
	glDrawArrays( GL_TRIANGLES, 0, 18);

	// Draw all children
	VisualObject::draw();
}// end draw

void Pyramid::setShaderValues()
{
	// Bind the shader 
	glUseProgram(shaderProgram);

	// Find the location of the model matrix uniform variable in the shader 
	modelLocation = glGetUniformLocation(shaderProgram, "modelMatrix"); 
	assert(modelLocation != 0xFFFFFFFF);
	// Find the locations of the material properties in the Material struct called 
	// object 
	material.setUpMaterial( getUniformLocation( shaderProgram, "object.ambientMat"), 
		getUniformLocation( shaderProgram, "object.diffuseMat"), 
		getUniformLocation( shaderProgram, "object.specularMat"), 
		getUniformLocation( shaderProgram, "object.specularExp"), 
		getUniformLocation( shaderProgram, "object.emissiveMat" ), 
		getUniformLocation( shaderProgram, "object.textureMapped"));
}