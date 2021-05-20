//texture vertex shader

#version 400 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 tex_coords;

void main()
{
    gl_Position = vec4(pos, 1.0);
    tex_coords = tex;
}