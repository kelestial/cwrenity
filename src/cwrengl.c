/*
*  ██████╗██╗    ██╗██████╗ ███████╗███╗   ██╗ ██████╗ ██╗     
* ██╔════╝██║    ██║██╔══██╗██╔════╝████╗  ██║██╔════╝ ██║     
* ██║     ██║ █╗ ██║██████╔╝█████╗  ██╔██╗ ██║██║  ███╗██║     
* ██║     ██║███╗██║██╔══██╗██╔══╝  ██║╚██╗██║██║   ██║██║     
* ╚██████╗╚███╔███╔╝██║  ██║███████╗██║ ╚████║╚██████╔╝███████╗
*  ╚═════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝
* 
* Cwrenity is a lightweight, data-oriented game framework!
*
*
* Copyright (c) 2021 Victor Sarkisov
*
* This library/source is free (as in free beer and speech): you can
* redistribute it and/or modify it under the terms of the 
* Apache License 2.0 as published by the Apache Software Foundation.
* No warranty or liability is given with the use of this library
* or any of its contents.
*/

#include <cwrengl.h>
#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>

static vert_array_t VAO;
static vert_buffer_t *VBO;
static shader_t SHADER;

static const char *V_SRC = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

static const char *F_SRC = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

static float vertices[6] = 
{
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.0f,  0.5f
}; 

void cgl_clear_colour(float r, float g, float b, float a)
{
	glClear(CGL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

void cgl_draw_arrays(unsigned int mode, int first, int count)
{
	glDrawArrays(mode, first, count);
}

vert_array_t cgl_gen_vertex_array()
{
	vert_array_t va;
	glGenVertexArrays(1, &va);
	return va;
}

void cgl_bind_vertex_array(vert_array_t va)
{
	glBindVertexArray(va);
}

void cgl_unbind_vertex_array()
{
	glBindVertexArray(0);
}

vert_buffer_t *cgl_gen_buffer(unsigned int type)
{
	vert_buffer_t *vb;

	vb = malloc(sizeof(struct vert_buffer_t));
	glGenBuffers(1, &vb->id);

	vb->type = type;
	return vb;
}

void cgl_bind_buffer(vert_buffer_t *vb)
{
	glBindBuffer(vb->type, vb->id);
}

void cgl_unbind_buffer(vert_buffer_t *vb)
{
	glBindBuffer(vb->type, 0);
}

void cgl_buffer_data(vert_buffer_t *vb, unsigned int size, void *data, unsigned int draw_type)
{
	glBufferData(vb->type, size, data, draw_type);
}

void cgl_buffer_attrib(vert_buffer_t *vb, unsigned int index, unsigned int size, unsigned int type, unsigned int stride, int pointer)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)pointer);
}

void cgl_dispose_buffer(vert_buffer_t *vb)
{
	glDeleteBuffers(1, &vb->id);
	free(vb);
}

shader_t cgl_create_shader(const char *vert, const char *frag)
{
	shader_t program = glCreateProgram();

	shader_t vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vert, NULL);
	glCompileShader(vs);

	shader_t fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &frag, NULL);
	glCompileShader(fs);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void cgl_enable_shader(shader_t shader)
{
	glUseProgram(shader);
}

void cgl_dispose_shader(shader_t shader)
{
	glDeleteProgram(shader);
}

void cgl_prepare_test()
{
	VAO = cgl_gen_vertex_array();
	VBO = cgl_gen_buffer(GL_ARRAY_BUFFER);

	cgl_bind_vertex_array(VAO);

	cgl_bind_buffer(VBO);
	cgl_buffer_data(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	cgl_buffer_attrib(VBO, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);

	cgl_unbind_vertex_array();

	SHADER = cgl_create_shader(V_SRC, F_SRC);
}

void cgl_render_test()
{
	cgl_bind_vertex_array(VAO);
	cgl_enable_shader(SHADER);
	cgl_draw_arrays(GL_TRIANGLES, 0, 3);
}

void cgl_cleanup_test()
{
	cgl_dispose_buffer(VBO);
	cgl_dispose_shader(SHADER);
}