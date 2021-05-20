//solid colour fragment shader

#version 400 core

out vec4 out_Colour;
uniform vec4 u_Colour;

void main()
{
	out_Colour = u_Colour;
}