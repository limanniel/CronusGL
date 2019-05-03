#version 330 core

// Input from vertex shader
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Output to the screen
out vec3 color;

// Handles
uniform sampler2D myTextureSampler;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;
//uniform vec3 LightColour;

void main(){
	vec3 LightColour = vec3(1,1,1);
	float LightPower = 50.0f;

	vec3 MaterialDiffuseColour = texture(myTextureSampler, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColour;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

	float distance = length(LightPosition_worldspace - Position_worldspace);
	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);

	// Specular
	vec3 Eye_Vector = normalize(EyeDirection_cameraspace);
	vec3 Reflect_Direction = reflect(-l,n);
	float cosAlpha = clamp(dot(Eye_Vector, Reflect_Direction), 0, 1);

	float cosTheta = clamp(dot(n,l), 0, 1);
	color = MaterialAmbientColor + MaterialDiffuseColour * LightColour * LightPower * cosTheta / (distance * distance) + MaterialSpecularColor * LightColour * LightPower * pow(cosAlpha,5) / (distance*distance);
}