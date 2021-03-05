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

/*
#############################################
#         	  BASE GL FUNCTIONS             #
#############################################
*/

CWRENGL_API void cgl_clear_colour(float r, float g, float b, float a);
CWRENGL_API void cgl_draw_arrays(unsigned int mode, int first, int count);
CWRENGL_API void cgl_draw_elements(unsigned int mode, int count, unsigned int type, void *indicies);

/*
#############################################
#               VERTEX ARRAYS               #
#############################################
*/

typedef unsigned int vert_array_t;

CWRENGL_API vert_array_t cgl_gen_vertex_array();
CWRENGL_API void cgl_bind_vertex_array(vert_array_t va);
CWRENGL_API void cgl_unbind_vertex_array();

/*
#############################################
#              VERTEX BUFFERS               #
#############################################
*/

typedef struct vert_buffer_t
{
	unsigned int id, type;
} vert_buffer_t;

CWRENGL_API vert_buffer_t *cgl_gen_buffer(unsigned int type);
CWRENGL_API void cgl_bind_buffer(vert_buffer_t *vb);
CWRENGL_API void cgl_unbind_buffer(vert_buffer_t *vb);
CWRENGL_API void cgl_buffer_data(vert_buffer_t *vb, unsigned int size, void *data, unsigned int draw_type);
CWRENGL_API void cgl_buffer_attrib(vert_buffer_t *vb, unsigned int index, unsigned int size, unsigned int type, unsigned int stride, int pointer);
CWRENGL_API void cgl_dispose_buffer(vert_buffer_t *vb);

/*
#############################################
#                  SHADERS                  #
#############################################
*/

typedef unsigned int shader_t;

CWRENGL_API shader_t cgl_create_shader(const char *vert, const char *frag);
CWRENGL_API void cgl_enable_shader(shader_t shader);
CWRENGL_API void cgl_dispose_shader(shader_t shader);

/*
#############################################
#                API TESTING                #
#############################################
*/

CWRENGL_API void cgl_prepare_test();
CWRENGL_API void cgl_render_test();
CWRENGL_API void cgl_cleanup_test();

#endif