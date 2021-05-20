#include <cwrenity.h>
#include <cwrengl.h>

#ifndef _APP_H_
#define _APP_H_

static cgl_vert_array_t va_array;

static cgl_vert_buffer_t *vb_ebo;
static cgl_vert_buffer_t *vb_pos;

static cgl_shader_t s_shader;
static cgl_texture_t *txr_box;

static float data_vert[16] = 
{
	 0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.0f, 1.0f
};

static unsigned int data_ind[6] = 
{
	0, 1, 3,
	1, 2, 3
};

void init_game_app()
{
	va_array = cgl_gen_vertex_array();
	vb_pos = cgl_gen_buffer(CGL_ARRAY_BUFFER);
	vb_ebo = cgl_gen_buffer(CGL_ELEMENT_ARRAY_BUFFER);

	s_shader = cgl_create_shader(cw_load_file("resources/shaders/purple.vert"), cw_load_file("resources/shaders/purple.frag"));

	cgl_bind_vertex_array(va_array);

	cgl_bind_buffer(vb_ebo);
	cgl_buffer_data(vb_ebo, sizeof(data_ind), data_ind, CGL_STATIC_DRAW);

	cgl_bind_buffer(vb_pos);
	cgl_buffer_data(vb_pos, sizeof(data_vert), data_vert, CGL_STATIC_DRAW);

	cgl_buffer_attrib(0, 2, CGL_FLOAT, 4 * sizeof(float), 0);
	cgl_buffer_attrib(1, 2, CGL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));

	cgl_unbind_vertex_array();
}

void update_game_app()
{
	//TODO: update logic here!
}

void render_game_app()
{
	cgl_clear_colour(0.0f, 0.0f, 0.0f, 1.0f);

	//txr_box = cgl_create_texture();
	//cgl_bind_texture(txr_box, 0);
	cgl_bind_vertex_array(va_array);
	cgl_enable_shader(s_shader);
	cgl_draw_elements(CGL_TRIANGLES, 6, CGL_UNSIGNED_INT, 0);
}

void terminate_game_app()
{
	cgl_dispose_buffer(vb_ebo);
	cgl_dispose_buffer(vb_pos);
	cgl_dispose_shader(s_shader);
}

#endif