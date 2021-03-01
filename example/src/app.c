#include <cwrenity.h>

#include "app.h"

void init_game_app()
{
	cw_log_message("Game Initialised!", NOTE);
	cw_log_message("Careful, now!", WARNING);
	cw_log_message("oops!, that was bad.", ERR);
	cw_log_message("I can't recover!", FATAL);
}

void update_game_app()
{
	
}

void draw_game_app()
{

}

void terminate_game_app()
{
	cw_log_message("Terminated App", NOTE);
}