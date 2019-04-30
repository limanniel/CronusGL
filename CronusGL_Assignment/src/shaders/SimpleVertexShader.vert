#version 330 core

// Inputs
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal;

// Outputs to fragment shader
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

// Handles
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 LightPosition_worldspace;

void main(){
	gl_Position = MVP * vec4(VertexPosition, 1);

	Position_worldspace = (M * vec4(VertexPosition,1)).xyz;

	// Vector that goes to camera in camera space from 0,0,0 origin
	vec3 vertexPosition_cameraspace = (V * M * vec4(VertexPosition,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	Normal_cameraspace = (V * M * vec4(VertexNormal, 0)).xyz;

	UV = VertexUV;
}