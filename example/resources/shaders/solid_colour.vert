//solid colour vertex shader

#version 400 core

layout (location = 0) in vec3 pos;

void main()
{
	gl_Position = pos;
}