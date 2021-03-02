#include <cwrenity.h>

#include "app.h"

int main(int argc, char const *argv[])
{
	app_info_t info = 
	{
		"cwrenity - calm coding!",	//title
		800, 600,					//window_size
		false						//vsync
	};

	cw_app_callbacks(init_game_app, update_game_app, draw_game_app, terminate_game_app);
	cw_break_point();
	cw_construct_app(info);

	return 0;
}