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

	cw_app_callbacks(init_game_app, update_game_app, render_game_app, terminate_game_app);
	cw_construct_app(info);

	//framework takes control of code execution from here

	return 0;
}