#include <cwrenity.h>

#include "app.h"

int main(int argc, char const *argv[])
{
	app_info_t info = {"cwrenity - calm coding!", 800, 0, false};

	cw_app_callbacks(init_game_app, update_game_app, draw_game_app, terminate_game_app);
	cw_construct_app(info);
	cw_destroy_app();

	return 0;
}