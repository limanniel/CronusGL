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

void main(){
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 50.0f;

	vec3 MaterialDiffuseColour = texture(myTextureSampler, UV).rgb;

	float distance = length(LightPosition_worldspace - Position_worldspace);

	vec3 n = normalize(Normal_cameraspace);
	vec3 l = normalize(LightDirection_cameraspace);

	float cosTheta = clamp(dot(n,l), 0, 1);
	color = MaterialDiffuseColour * LightColor * LightPower * cosTheta / (distance * distance);
}