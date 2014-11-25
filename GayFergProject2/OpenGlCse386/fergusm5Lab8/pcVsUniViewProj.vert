// Targeting version 3.3 of GLSL. If the compiler does not support 
// 3.3 it will cause an error.
#version 330
layout (std140) uniform projectionViewBlock 
{ 
	mat4 projectionMatrix; 
	mat4 viewMatrix; 
};

uniform mat4 modelMatrix;

// Declares that a vertex specific attribute which is a vector of 3 floats
// will be known as 'Position' in the shader. 'Vertex specific' means that 
// for every invocation of the shader in the GPU the value of a new vertex 
// from the buffer will be supplied. The first section of the statement, 
// layout (location = 0), creates the binding between the attribute name 
// and attribute in the buffer. This is required for cases where the vertex 
// contains several attributes (position, normal, texture coordinates, etc).

layout (location = 0) in vec3 vertexPosition; 
layout (location = 1) in vec3 vertexNormal;

out vec3 Normal0;
out vec3 WorldPos0;

// There can only be one main function for each shader stage
void main()
{

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0f);
	
	// Calculate position in world coordinates
	WorldPos0 =(modelMatrix * vec4(vertexPosition, 1.0f)).xyz;

	// Calculate normal in world coordinates
	Normal0 = normalize(mat3(modelMatrix) * vertexNormal);
}