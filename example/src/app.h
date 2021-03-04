#include <cwrenity.h>
#include <cwrengl.h>

#ifndef _APP_H_
#define _APP_H_

void init_game_app()
{
	cgl_prepare_test();
}

void update_game_app()
{
	
}

void render_game_app()
{
	cgl_clear_colour(0.4f, 0.2f, 0.6f, 1.0f);
	cgl_update_test();
}

void terminate_game_app()
{
	cw_log_message("Terminated App", NOTE);
}

#endif