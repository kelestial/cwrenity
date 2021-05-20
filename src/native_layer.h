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

//windowing controls
CWREN_INT void native_create_window(const char *title, unsigned int width, unsigned int height);
CWREN_INT void native_show_window(bool win_show);
CWREN_INT void native_set_window_title(const char *title);
CWREN_INT void native_set_window_size(int width, int height);
CWREN_INT void native_set_window_fullscreen();
CWREN_INT void native_set_window_borderless();
CWREN_INT void native_set_window_bordered();

CWREN_INT void native_update_window();
CWREN_INT void native_destroy_window();
CWREN_INT bool native_is_window_alive();

//opengl context controls
CWREN_INT void native_create_gl_context(bool vsync);
CWREN_INT void native_destroy_gl_context();

//console/debugging controls
CWREN_INT void native_console_colour(int colour);
CWREN_INT void native_debug_break();