//purple fragment shader

#version 400 core

in vec4 pos_Colour;
out vec4 out_Colour;

void main()
{
	out_Colour = pos_Colour;
}