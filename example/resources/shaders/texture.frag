//texture fragment shader

#version 400 core

out vec4 frag_colour;
in vec2 tex_coords;

uniform sampler2D u_txr_id;

void main()
{
    frag_colour = texture(u_txr_id, tex_coords);
}