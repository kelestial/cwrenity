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

static vert_array_t VAO;
static vert_buffer_t *VBO;
static vert_buffer_t *EBO;
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

static float VERTICES[8] = 
{
	 0.5f,  0.5f,
	 0.5f, -0.5f,
	-0.5f, -0.5f,
	-0.5f,  0.5f
};

static unsigned int INDICIES[6] = 
{
	0, 1, 3,
	1, 2, 3
}; 

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

void cgl_prepare_test()
{
	VAO = cgl_gen_vertex_array();
	VBO = cgl_gen_buffer(CGL_ARRAY_BUFFER);
	EBO = cgl_gen_buffer(CGL_ELEMENT_ARRAY_BUFFER);

	cgl_bind_vertex_array(VAO);

	cgl_bind_buffer(EBO);
	cgl_buffer_data(EBO, sizeof(INDICIES), INDICIES, CGL_STATIC_DRAW);

	cgl_bind_buffer(VBO);
	cgl_buffer_data(VBO, sizeof(VERTICES), VERTICES, CGL_STATIC_DRAW);
	cgl_buffer_attrib(VBO, 0, 2, CGL_FLOAT, 2 * sizeof(float), 0);

	cgl_unbind_vertex_array();

	SHADER = cgl_create_shader(V_SRC, F_SRC);
}

void cgl_render_test()
{
	cgl_bind_vertex_array(VAO);
	cgl_enable_shader(SHADER);

	cgl_draw_elements(CGL_TRIANGLES, 6, CGL_UNSIGNED_INT, 0);
}

void cgl_cleanup_test()
{
	cgl_dispose_buffer(VBO);
	cgl_dispose_shader(SHADER);
}