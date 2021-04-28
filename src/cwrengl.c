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

#include <cwrenity.h>
#include <cwrengl.h>

#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

#define GLCALL(x) gl_clear_errors(); x; gl_poll_errors();
 

static void gl_clear_errors()
{
	while (glGetError() != GL_NO_ERROR);
}

static void gl_poll_errors()
{
	unsigned int error;

	while (error = glGetError())
	{
		//TODO: use cwrenity logger
		//TODO: translate error to string

		printf("ERROR: (cwrengl) gl error code: %i\n", error);
	}
}

/*
#############################################
#             BASE GL FUNCTIONS             #
#############################################
*/

void cgl_clear_colour(float r, float g, float b, float a)
{
	GLCALL(glClear(CGL_COLOR_BUFFER_BIT));
	GLCALL(glClearColor(r, g, b, a));
}

void cgl_draw_arrays(unsigned int mode, int first, int count)
{
	GLCALL(glDrawArrays(mode, first, count));
}

void cgl_draw_elements(unsigned int mode, int count, unsigned int type, void *indicies)
{
	GLCALL(glDrawElements(mode, count, type, indicies));
}

void cgl_set_viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
#############################################
#               VERTEX ARRAYS               #
#############################################
*/

vert_array_t cgl_gen_vertex_array()
{
	vert_array_t va;
	GLCALL(glGenVertexArrays(1, &va));
	return va;
}

void cgl_bind_vertex_array(vert_array_t va)
{
	GLCALL(glBindVertexArray(va));
}

void cgl_unbind_vertex_array()
{
	GLCALL(glBindVertexArray(0));
}

/*
#############################################
#              VERTEX BUFFERS               #
#############################################
*/

vert_buffer_t *cgl_gen_buffer(unsigned int type)
{
	vert_buffer_t *vb;

	vb = malloc(sizeof(struct vert_buffer_t));
	GLCALL(glGenBuffers(1, &vb->id));

	vb->type = type;
	return vb;
}

void cgl_bind_buffer(vert_buffer_t *vb)
{
	GLCALL(glBindBuffer(vb->type, vb->id));
}

void cgl_unbind_buffer(vert_buffer_t *vb)
{
	GLCALL(glBindBuffer(vb->type, 0));
}

void cgl_buffer_data(vert_buffer_t *vb, unsigned int size, void *data, unsigned int draw_type)
{
	GLCALL(glBufferData(vb->type, size, data, draw_type));
}

void cgl_buffer_attrib(vert_buffer_t *vb, unsigned int index, unsigned int size, unsigned int type, unsigned int stride, int pointer)
{
	GLCALL(glEnableVertexAttribArray(index));
	GLCALL(glVertexAttribPointer(index, size, type, CGL_FALSE, stride, (void*)pointer));
}

void cgl_dispose_buffer(vert_buffer_t *vb)
{
	GLCALL(glDeleteBuffers(1, &vb->id));
	free(vb);
}

/*
#############################################
#                  SHADERS                  #
#############################################
*/

shader_t cgl_create_shader(const char *vert, const char *frag)
{
	shader_t program = glCreateProgram();

	shader_t vs = glCreateShader(CGL_VERTEX_SHADER);
	GLCALL(glShaderSource(vs, 1, &vert, NULL));
	GLCALL(glCompileShader(vs));

	shader_t fs = glCreateShader(CGL_FRAGMENT_SHADER);
	GLCALL(glShaderSource(fs, 1, &frag, NULL));
	GLCALL(glCompileShader(fs));

	GLCALL(glAttachShader(program, vs));
	GLCALL(glAttachShader(program, fs));
	GLCALL(glLinkProgram(program));

	GLCALL(glDeleteShader(vs));
	GLCALL(glDeleteShader(fs));

	return program;
}

void cgl_enable_shader(shader_t shader)
{
	GLCALL(glUseProgram(shader));
}

void cgl_dispose_shader(shader_t shader)
{
	GLCALL(glDeleteProgram(shader));
}

void cgl_shader_uniform_4f(shader_t shader, const char *uniform, float f1, float f2, float f3, float f4)
{
	int loc = glGetUniformLocation(shader, uniform);
	GLCALL(glUniform4f(loc, f1, f2, f3, f4));
}