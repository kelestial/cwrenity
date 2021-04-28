//rainbow vertex shader

#version 400 core

layout (location = 0) in vec4 pos;
out vec4 pos_Colour;

void main()
{
	gl_Position = pos;
    pos_Colour = pos;
}