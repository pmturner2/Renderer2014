#version 150 core

uniform sampler2D diffuse;

in vec2 pass_tc;

out vec4 out_Color;

void main(void)
{
	//out_Color = vec4(pass_tc.xy, 0.0, 1.0);
	out_Color = texture2D (diffuse, pass_tc);
	//out_Color = vec4(0,0,1,1);
}