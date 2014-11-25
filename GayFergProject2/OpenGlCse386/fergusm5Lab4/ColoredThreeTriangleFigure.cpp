#include "ColoredThreeTriangleFigure.h"


ColoredThreeTriangleFigure::ColoredThreeTriangleFigure(void)
{
}


ColoredThreeTriangleFigure::~ColoredThreeTriangleFigure(void)
{
}

void ColoredThreeTriangleFigure::initialize() 
{
	GLuint VBO, CBO;
	glGenVertexArrays (1, &vertexArrayObject);
	glBindVertexArray( vertexArrayObject );
	glm::vec3 v0 = glm::vec3(-0.7f, 0.0f, 0.0f);
	glm::vec3 v1 = glm::vec3(-0.3f, 0.0f, 0.0f);
	glm::vec3 v2 = glm::vec3(-0.5f, 0.5f, 0.0f);
	glm::vec3 v3 = glm::vec3(-0.2f, 0.0f, 0.0f);
	glm::vec3 v4 = glm::vec3(0.0f, -0.5f, 0.0f);
	glm::vec3 v5 = glm::vec3(0.2f, 0.0f, 0.0f);
	glm::vec3 v6 = glm::vec3(0.3f, 0.0f, 0.0f);
	glm::vec3 v7 = glm::vec3(0.7f, 0.0f, 0.0f);
	glm::vec3 v8 = glm::vec3(0.5f, 0.5f, 0.0f);

	vector<glm::vec3> v;
	v.push_back( v0 );
	v.push_back( v1 );
	v.push_back( v2 );
	v.push_back( v3 );
	v.push_back( v4 );
	v.push_back( v5 );
	v.push_back( v6 );
	v.push_back( v7 );
	v.push_back( v8 );
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(glm::vec3), &v[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	vector<glm::vec4> c;
	glm::vec4 c0 = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 c1 = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec4 c2 = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < 3; i++)
	{
		c.push_back(c0);
	}
	for (int i = 0; i < 3; i++)
	{
		c.push_back(c1);
	}
	c.push_back(c0);
	c.push_back(c1);
	c.push_back(c2);
	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, c.size() * sizeof(glm::vec4), &c[0],
		GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}

void ColoredThreeTriangleFigure::draw() 
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 9 );
}