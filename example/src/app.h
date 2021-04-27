#include <cwrenity.h>
#include <cwrengl.h>

#ifndef _APP_H_
#define _APP_H_

static vert_array_t VAO;
static vert_buffer_t *VBO;
static vert_buffer_t *EBO;
static shader_t SHADER;

static const char *V_SRC = "#version 400 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

static const char *F_SRC = "#version 400 core\n"
	"uniform vec4 u_Colour;\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"FragColor = u_Colour;\n"
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

void init_game_app()
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

void update_game_app()
{
	//TODO: update logic here!
}

void render_game_app()
{
	cgl_clear_colour(0.4f, 0.2f, 0.6f, 1.0f);

	cgl_bind_vertex_array(VAO);

	cgl_enable_shader(SHADER);
	cgl_shader_uniform_4f(SHADER, "u_Colour", 1, 0, 1, 1);

	cgl_draw_elements(CGL_TRIANGLES, 6, CGL_UNSIGNED_INT, 0);
}

void terminate_game_app()
{
	cw_log_message("Terminated App", NOTE);
	cgl_dispose_buffer(VBO);
	cgl_dispose_shader(SHADER);
}

#endif