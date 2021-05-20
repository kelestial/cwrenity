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

#ifndef _CWRENGL_H_
#define _CWRENGL_H_

#if defined(CWREN_PLATFORM_WIN) && defined(CWREN_BUILD_SHARED)
#	define CWRENGL_API __declspec(dllexport)
#elif defined (CWREN_PLATFORM_WIN)
#	define CWRENGL_API __declspec(dllimport)
#elif defined (CWREN_PLATFORM_UNIX) && defined(CWREN_BUILD_SHARED)
#	define CWRENGL_API __attribute__((visibility("default")))
#else
#	define CWRENGL_API
#endif

#define CGL_COLOR_BUFFER_BIT 0x00004000

#define CGL_TRIANGLES 0x0004

#define CGL_ARRAY_BUFFER 0x8892
#define CGL_ELEMENT_ARRAY_BUFFER 0x8893

#define CGL_FALSE 0
#define CGL_TRUE 1

#define CGL_STREAM_DRAW 0x88E0
#define CGL_STREAM_READ 0x88E1
#define CGL_STREAM_COPY 0x88E2
#define CGL_STATIC_DRAW 0x88E4
#define CGL_STATIC_READ 0x88E5
#define CGL_STATIC_COPY 0x88E6
#define CGL_DYNAMIC_DRAW 0x88E8
#define CGL_DYNAMIC_READ 0x88E9
#define CGL_DYNAMIC_COPY 0x88EA

#define CGL_BYTE 0x1400
#define CGL_UNSIGNED_BYTE 0x1401
#define CGL_SHORT 0x1402
#define CGL_UNSIGNED_SHORT 0x1403
#define CGL_INT 0x1404
#define CGL_UNSIGNED_INT 0x1405
#define CGL_FLOAT 0x1406

#define CGL_FRAGMENT_SHADER 0x8B30
#define CGL_VERTEX_SHADER 0x8B31

#define CGL_CLAMP_TO_EDGE 0x812F

#define CGL_RGBA 0x1908

#define CGL_TEXTURE0 0x84C0
#define CGL_TEXTURE1 0x84C1
#define CGL_TEXTURE2 0x84C2
#define CGL_TEXTURE3 0x84C3
#define CGL_TEXTURE4 0x84C4
#define CGL_TEXTURE5 0x84C5
#define CGL_TEXTURE6 0x84C6
#define CGL_TEXTURE7 0x84C7
#define CGL_TEXTURE8 0x84C8
#define CGL_TEXTURE9 0x84C9
#define CGL_TEXTURE10 0x84CA
#define CGL_TEXTURE11 0x84CB
#define CGL_TEXTURE12 0x84CC
#define CGL_TEXTURE13 0x84CD
#define CGL_TEXTURE14 0x84CE
#define CGL_TEXTURE15 0x84CF
#define CGL_TEXTURE16 0x84D0
#define CGL_TEXTURE17 0x84D1
#define CGL_TEXTURE18 0x84D2
#define CGL_TEXTURE19 0x84D3
#define CGL_TEXTURE20 0x84D4
#define CGL_TEXTURE21 0x84D5
#define CGL_TEXTURE22 0x84D6
#define CGL_TEXTURE23 0x84D7
#define CGL_TEXTURE24 0x84D8
#define CGL_TEXTURE25 0x84D9
#define CGL_TEXTURE26 0x84DA
#define CGL_TEXTURE27 0x84DB
#define CGL_TEXTURE28 0x84DC
#define CGL_TEXTURE29 0x84DD
#define CGL_TEXTURE30 0x84DE
#define CGL_TEXTURE31 0x84DF

#define CGL_TEXTURE_2D 0x0DE1
#define CGL_TEXTURE_MAG_FILTER 0x2800
#define CGL_TEXTURE_MIN_FILTER 0x2801
#define CGL_TEXTURE_WRAP_S 0x2802
#define CGL_TEXTURE_WRAP_T 0x2803

#define CGL_NEAREST 0x2600
#define CGL_LINEAR 0x2601

#define CGL_NO_ERROR 0

/*
#############################################
#             BASE GL FUNCTIONS             #
#############################################
*/

CWRENGL_API void cgl_clear_colour(float r, float g, float b, float a);
CWRENGL_API void cgl_draw_arrays(unsigned int mode, int first, int count);
CWRENGL_API void cgl_draw_elements(unsigned int mode, int count, unsigned int type, void *indicies);
CWRENGL_API void cgl_set_viewport(int width, int height);

/*
#############################################
#               VERTEX ARRAYS               #
#############################################
*/

typedef unsigned int cgl_vert_array_t;

CWRENGL_API cgl_vert_array_t cgl_gen_vertex_array();
CWRENGL_API void cgl_bind_vertex_array(cgl_vert_array_t va);
CWRENGL_API void cgl_unbind_vertex_array();

/*
#############################################
#              VERTEX BUFFERS               #
#############################################
*/

typedef struct cgl_vert_buffer_t
{
	unsigned int id, type;
} cgl_vert_buffer_t;

CWRENGL_API cgl_vert_buffer_t *cgl_gen_buffer(unsigned int type);
CWRENGL_API void cgl_bind_buffer(cgl_vert_buffer_t *vb);
CWRENGL_API void cgl_unbind_buffer(cgl_vert_buffer_t *vb);
CWRENGL_API void cgl_buffer_data(cgl_vert_buffer_t *vb, unsigned int size, void *data, unsigned int draw_type);
CWRENGL_API void cgl_buffer_attrib(cgl_vert_buffer_t *vb, unsigned int index, unsigned int size, unsigned int type, unsigned int stride, int pointer);
CWRENGL_API void cgl_dispose_buffer(cgl_vert_buffer_t *vb);

/*
#############################################
#                  SHADERS                  #
#############################################
*/

typedef unsigned int cgl_shader_t;

CWRENGL_API cgl_shader_t cgl_create_shader(const char *vert, const char *frag);
CWRENGL_API void cgl_enable_shader(cgl_shader_t shader);
CWRENGL_API void cgl_dispose_shader(cgl_shader_t shader);
CWRENGL_API void cgl_shader_uniform_4f(cgl_shader_t shader, const char *uniform, float f1, float f2, float f3, float f4);

/*
#############################################
#                 TEXTURES                  #
#############################################
*/

typedef struct cgl_texture_t
{
	unsigned int id; 
} cgl_texture_t;

CWRENGL_API cgl_texture_t *cgl_create_texture();
CWRENGL_API void cgl_dispose_texture(cgl_texture_t *texture);
CWRENGL_API void cgl_bind_texture(cgl_texture_t *texture, unsigned int slot);
CWRENGL_API void cgl_unbind_texture();


#endif