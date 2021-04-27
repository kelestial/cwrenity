//solid colour fragment shader

#version 400 core

uniform vec4 u_Colour;
out vec4 out_Colour;

void main()
{
	out_Colour = u_Colour;
}