#version 150 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

in vec3 in_Position;
in vec2 in_TexCoord;

in vec3 in_Tangent;
in vec3 in_Normal;

out vec2 pass_tc;

void main(void)
{
	// Move multiplication chain to CPU?
	
	pass_tc = in_TexCoord;
	pass_tc.y = 1.0 - pass_tc.y;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0); 
	
}