// Specifying version of GLSL. If the compiler does not support 
// this version of higher, an error will occur.
#version 330

#pragma optimize(off)
#pragma debug(on)

// Declare default precision - eliminates warnings (but can cause an error on some machines)
precision mediump float;

// Structure for holding general light properties
struct GeneralLight {
  
	vec4 ambientColor;		// ambient color of the light
	vec4 diffuseColor;		// diffuse color of the light
    vec4 specularColor;		// specular color of the light

	// Either the position or direction
	// if w = 0 then the light is directional and direction specified 
	// is the negative of the direction the light is shinning
	// if w = 1 then the light is positional
    vec4 positionOrDirection;    
					  
	// spotlight attributes
    vec3 spotDirection;		// the direction the cone of light is shinning    
	int isSpot;				// 1 if the light is a spotlight  
    float spotCutoffCos;	// Cosine of the spot cutoff angle
    float spotExponent;		// For gradual falloff near cone edge

	// attenuation coefficients
    float constant; 
    float linear;
    float quadratic;

	int enabled;			// 1 if light is "on"

};

// Structure for material properties
struct Material
{
	vec4 ambientMat;

	vec4 diffuseMat;

	vec4 specularMat;

	float specularExp;

	vec4 emissiveMat;

	bool textureMapped;
};

const int MaxLights = 8;

layout (std140) uniform LightBlock
{
	GeneralLight lights[MaxLights];
};


uniform Material object;

// Sampler to determine interpolated texture coordinates for the fragment 
uniform sampler2D gSampler;

layout (std140) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

// Vertex attributes passed in by the vertex shader
in vec3 Normal0;
in vec3 WorldPos0;  
in vec2 TexCoord0;

// Output color for the fragment (pixel)
out vec4 FragColor;

vec4 calcLight( GeneralLight light, Material object )
{
	vec4 totalLight = vec4(0.0f,0.0f,0.0f,1.0f);
	
	if(light.enabled == 1) {	
		vec3 directionToLight = vec3(light.positionOrDirection.xyz);

		//Direct light
		if (light.positionOrDirection.w < 1) {

		}

		//Pos light
		else {
			// Find a unit vector that points at the light source
			directionToLight = normalize(light.positionOrDirection.xyz - WorldPos0 );	
		}

		//Ambient
		vec4 ambient = object.ambientMat * light.ambientColor;

		//Diffuse
        vec4 diffuse = max(dot(Normal0, directionToLight), 0.0f) * object.diffuseMat * light.diffuseColor;

        //Specular
        vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
        vec3 LightReflect = normalize(reflect(-directionToLight, Normal0) );
        float SpecularFactor = max(dot(VertexToEye, LightReflect ), 0.0f);
        SpecularFactor = pow(SpecularFactor, object.specularExp);
        vec4 specular = SpecularFactor * object.specularMat * light.specularColor;
		
		totalLight = ambient + diffuse + specular;

		float spotLightEffect = 1.0f;

		//Spotlight
		if (light.isSpot == 1) {
			vec3 LightToPixel= -directionToLight;//normalize(WorldPos0 - light.positionOrDirection.xyz);
			float spotCosFactor= dot(LightToPixel, light.spotDirection);

			if( spotCosFactor > light.spotCutoffCos ) {
				vec3 directionToSpotLight = - LightToPixel;

				// Diffuse
				diffuse = max(dot(Normal0, directionToSpotLight), 0.0f) * object.diffuseMat * light.diffuseColor;
			
				// Specular
				vec3 VertexToEye = normalize(worldEyePosition - WorldPos0);
				vec3 LightReflect = normalize(reflect(-directionToSpotLight, Normal0));
				float SpecularFactor = max(dot(VertexToEye, LightReflect), 0.0f);
				SpecularFactor= pow(SpecularFactor, object.specularExp);
				vec4 specularTerm = SpecularFactor *object.specularMat * light.specularColor;
				specular = diffuse + specularTerm;
			
				// Traditional method for attenuating illumination near the edges of the cone
				//float falloff = pow( spotCosFactor, 50.0f );
				// Alternative method for attenuating illumination near the edges of the cone
				spotLightEffect = 1.0f - (1.0f - spotCosFactor) /
				(1.0f - light.spotCutoffCos);
			} else {
				spotLightEffect = 0.0f;
			}
			totalLight = spotLightEffect * totalLight;			
		}		
	}

	return totalLight;
}

const vec4 fogColor = vec4(0.75f, 0.75f, 0.75f, 0.0f);
const float fogEnd = 25.0f;
const float fogStart = 1.0f;
const float fogDensity = 0.2f;
float distanceFromViewPoint;

float linearFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);
	return max((fogEnd - distanceFromViewPoint)/(fogEnd - fogStart), 0.0f);
}
float exponentialFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);
	return exp( -(fogDensity * distanceFromViewPoint));
}
float exponentialTwoFogFactor() {
	distanceFromViewPoint = distance(worldEyePosition, WorldPos0);
	return exp( - pow((fogDensity * distanceFromViewPoint),2));
}

void main() { 
	Material texturedMaterial = object;

	if (object.textureMapped == true) {
		texturedMaterial.ambientMat = texture2D(gSampler, TexCoord0.st); 
		texturedMaterial.diffuseMat = texture2D(gSampler, TexCoord0.st); 
		texturedMaterial.specularMat = texture2D(gSampler, TexCoord0.st); 
	}

	FragColor = object.emissiveMat;

	for (int i = 0; i < MaxLights; i++) { 
		FragColor += calcLight( lights[i], texturedMaterial ); 
	}

	float fogFactor = linearFogFactor();
	FragColor = fogFactor * FragColor + (1-fogFactor) * fogColor;

	FragColor.a = object.diffuseMat.a;
}