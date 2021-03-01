/*
*  ██████╗██╗    ██╗██████╗ ███████╗███╗   ██╗██╗████████╗██╗   ██╗
* ██╔════╝██║    ██║██╔══██╗██╔════╝████╗  ██║██║╚══██╔══╝╚██╗ ██╔╝
* ██║     ██║ █╗ ██║██████╔╝█████╗  ██╔██╗ ██║██║   ██║    ╚████╔╝ 
* ██║     ██║███╗██║██╔══██╗██╔══╝  ██║╚██╗██║██║   ██║     ╚██╔╝  
* ╚██████╗╚███╔███╔╝██║  ██║███████╗██║ ╚████║██║   ██║      ██║   
*  ╚═════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═╝   ╚═╝      ╚═╝
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

#include <cwrenity.h>
#include <stddef.h>

#include "native_layer.h"

static void (*app_callbacks[4])() = {NULL, NULL, NULL, NULL};

static void terminate_application()
{
	app_callbacks[3]();
}

static void core_application_cycle()
{
	app_callbacks[0]();

	while (native_is_window_alive())
	{
		app_callbacks[2]();
		app_callbacks[1]();
		native_update_window();
	}

	terminate_application();
}

void cw_app_callbacks(void (*init)(), void (*update)(), void (*render)(), void (*terminate)())
{
	app_callbacks[0] = init;
	app_callbacks[1] = update;
	app_callbacks[2] = render;
	app_callbacks[3] = terminate;
}

void cw_construct_app(app_info_t info)
{
	native_create_window(info.title, info.width, info.height);
	native_create_gl_context();
	native_show_window(true);
	
	core_application_cycle();
}

void cw_destroy_app()
{
	native_destroy_gl_context();
	native_destroy_window();
}