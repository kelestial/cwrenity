#include <cwrenity.h>

#include "app.h"

int main(int argc, char const *argv[])
{
	app_info_t info = 
	{
		init_game_app, update_game_app, render_game_app, terminate_game_app,	//callbacks
		"cwrenity - calm coding!",												//title
		1280, 720,																//window_size
		true																	//vsync
	};

	cw_construct_app(info);		//framework takes control of code execution from here!

	return 0;
}